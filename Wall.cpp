#include "Wall.h"
#include "Screen.h"

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>

Wall::Wall()
{
    gapHeight = 150;
    wallWidth = 70;
    wallLower.setSize(sf::Vector2f(wallWidth, rand() % (Screen::Height - gapHeight)));
    wallUpper.setSize(sf::Vector2f(wallWidth, Screen::Height - (wallLower.getSize().y + gapHeight)));
    wallLower.setPosition(0, Screen::Height - wallLower.getSize().y);
    wallUpper.setPosition(0, 0);
}

Wall::~Wall()
{
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(wallLower, states);
    target.draw(wallUpper, states);
}

int Wall::getWidth()
{
    return wallWidth;
}

sf::IntRect Wall::getLowerIntRect()
{
    return sf::IntRect(wallLower.getPosition().x, wallLower.getPosition().y,
            wallLower.getSize().x, wallLower.getSize().y);
}

sf::IntRect Wall::getUpperIntRect()
{
    return sf::IntRect(wallUpper.getPosition().x, wallUpper.getPosition().y,
            wallUpper.getSize().x, wallUpper.getSize().y);
}
