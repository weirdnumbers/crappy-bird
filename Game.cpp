#include "Game.h"
#include "Wall.h"
#include "Screen.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

Game::Game()
    : mWindow(sf::VideoMode(Screen::Width, Screen::Height), "Crappy Bird", sf::Style::Close)
{
    wallDistance = 220;
    jumpVelocity = - 600;
    gravity = 2000;
    birdVelocity = 0.f;
    wallSpeed = - 180;
    wasPressed = false;
    isPressed = false;
    paused = true;

    restart();
}

void Game::run()
{
    sf::Clock clock;

    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();

        handleInput();
        processEvents();
        update(elapsedTime);
        render();
    }
}

void Game::restart()
{
    mBird.setPosition(0.2 * Screen::Width, (Screen::Height - mBird.getSize().y)/ 2);
    paused = true;
    walls.clear();
    Wall newWall;
    newWall.setPosition(1.5 * Screen::Width, 0);
    walls.push_back(newWall);
}

void Game::loadTextures()
{
    textureManager.loadTexture("wall", "textures/brick.png");
}

void Game::moveBird(float timedelta)
{
    birdVelocity += timedelta * gravity;
    float offset = timedelta * (birdVelocity + timedelta * gravity / 2);

    mBird.move(0, offset);
}

void Game::handleInput()
{
    isPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if(isPressed && !wasPressed)
    {
        birdVelocity = jumpVelocity;
        wasPressed = true;
        paused = false;
    }
    else if(!isPressed && wasPressed)
    {
        wasPressed = false;
    }
}

void Game::handleCollisions()
{
    for(std::deque<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        sf::IntRect lowerIntRect = (*it).getLowerIntRect((*it).getPosition());
        sf::IntRect upperIntRect = (*it).getUpperIntRect((*it).getPosition());
        sf::IntRect birdIntRect = mBird.getIntRect(mBird.getPosition());

        if(birdIntRect.intersects(lowerIntRect) || birdIntRect.intersects(upperIntRect))
        {
            restart();
        }

        else if(mBird.getPosition().y + mBird.getSize().y <= 0 &&
                mBird.getPosition().x + mBird.getSize().x > (*it).getPosition().x &&
                mBird.getPosition().x < (*it).getPosition().x
                + (*it).getWidth())
        {
            restart();
        }
    }

}

void Game::checkBirdBounds()
{
    if(mBird.getPosition().y + mBird.getSize().y >= Screen::Height)
    {
        //mBird.setPosition(mBird.getPosition().x, Screen::Height - mBird.getSize().y);
        restart();
    }
}

void Game::processEvents()
{
    sf::Event event;

    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::moveWalls(float timedelta)
{
    for(std::deque<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        (*it).move(sf::Vector2f(timedelta * wallSpeed, 0));

        int distance = Screen::Width - (*it).getPosition().x - (*it).getWidth();

        if(it == --walls.end())
        {
            if(distance >= wallDistance)
            {
                Wall wall;
                wall.setPosition(Screen::Width, 0);
                walls.push_back(wall);
                break;
            }
        }

        if(distance >= Screen::Width)
        {
            walls.pop_front();
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    float timedelta = elapsedTime.asSeconds();

    if(!paused)
    {
        moveBird(timedelta);
        moveWalls(timedelta);
        checkBirdBounds();
        handleCollisions();
    }
}

void Game::render()
{
    mWindow.clear(sf::Color(0, 150, 255));

    for(std::deque<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        mWindow.draw(*it);
    }

    mWindow.draw(mBird);
    mWindow.display();
}
