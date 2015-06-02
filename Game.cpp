#include "Game.h"
#include "Wall.h"
#include "Screen.h"
#include <iostream>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

Game::Game()
    : mWindow(sf::VideoMode(Screen::Width, Screen::Height), "Crappy Bird", sf::Style::Close)
{
    mBird.setPosition(0.15 * Screen::Width, (Screen::Height - mBird.getSize().y)/ 2);
    wallDistance = 400;
    jumpVelocity = - 350;
    gravity = 1000;
    birdVelocity = 0.f;
    wallSpeed = - 200;
    wasPressed = false;
    isPressed = false;

    Wall firstWall;
    firstWall.setPosition(Screen::Width, 0);
    walls.push_back(firstWall);
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
    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        int distance = Screen::Width - (*it).getPosition().x - (*it).getWidth();

        (*it).move(sf::Vector2f(timedelta * wallSpeed, 0));

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
            walls.erase(it);
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    float timedelta = elapsedTime.asSeconds();

    moveBird(timedelta);
    moveWalls(timedelta);
}

void Game::render()
{
    mWindow.clear();

    for(std::vector<Wall>::iterator it = walls.begin(); it != walls.end(); ++it)
    {
        mWindow.draw(*it);
    }

    mWindow.draw(mBird);
    mWindow.display();
}
