#include "Bird.h"
#include "Screen.h"
#include <SFML/Graphics/Drawable.hpp>

Bird::Bird()
{
    mShape.setSize(sf::Vector2f(40, 40));
    mShape.setFillColor(sf::Color(250, 0, 0));
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape, states);
}

sf::Vector2f Bird::getSize()
{
    return mShape.getSize();
}
