#include "Wall.h"
#include "Screen.h"

#include <iostream>
#include <SFML/Graphics/Drawable.hpp>

Wall::Wall()
{
    gapHeight = 150;
    minHeight = 40;
    wallWidth = 70;
    wallLower.setSize(sf::Vector2f(wallWidth, minHeight + rand() % (Screen::Height
                    - 2 * minHeight - gapHeight)));
    wallUpper.setSize(sf::Vector2f(wallWidth, Screen::Height - gapHeight - wallLower.getSize().y));
    wallLower.setPosition(0, Screen::Height - wallLower.getSize().y);
    wallUpper.setPosition(0, 0);
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

sf::IntRect Wall::getLowerIntRect(const sf::Vector2f& position)
{
    return sf::IntRect(position.x, position.y + wallUpper.getSize().y + gapHeight,
            wallLower.getSize().x, wallLower.getSize().y);
}

sf::IntRect Wall::getUpperIntRect(const sf::Vector2f& position)
{
    return sf::IntRect(position.x, position.y, wallUpper.getSize().x, wallUpper.getSize().y);
}

sf::RectangleShape& Wall::getLowerWall()
{
    return wallLower;
}

sf::RectangleShape& Wall::getUpperWall()
{
    return wallUpper;
}
