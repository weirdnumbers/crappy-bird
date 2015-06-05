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
    mBird.setPosition(0.15 * Screen::Width, (Screen::Height - mBird.getSize().y)/ 2);
    walls.clear();
    Wall firstWall;
    firstWall.setPosition(Screen::Width, 0);
    walls.push_back(firstWall);
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
        mBird.setPosition(mBird.getPosition().x, Screen::Height - mBird.getSize().y);
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

    moveBird(timedelta);
    moveWalls(timedelta);
    checkBirdBounds();
    handleCollisions();
}

void Game::render()
{
    mWindow.clear();

    for(std::deque<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        mWindow.draw(*it);
    }

    mWindow.draw(mBird);
    mWindow.display();
}
