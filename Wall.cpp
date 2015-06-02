#include "Wall.h"

#include <SFML/Graphics/Drawable.hpp>

Wall::Wall()
{
    gapHeight = 120;
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
