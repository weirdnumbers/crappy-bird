#include "Game.h"
#include "Screen.h"
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>

Game::Game()
    : mWindow(sf::VideoMode(Screen::Width, Screen::Height), "Crappy Bird", sf::Style::Close)
{
    mBird.setPosition(0.15 * Screen::Width, (Screen::Height - mBird.getSize().y)/ 2);
    jumpVelocity = - 300;
    gravity = 700;
    birdVelocity = 0.f;
    wallWidth = 300;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        birdVelocity = jumpVelocity;
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

void Game::update(sf::Time elapsedTime)
{
    float timedelta = elapsedTime.asSeconds();
    moveBird(timedelta);
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mBird);
    mWindow.display();
}
