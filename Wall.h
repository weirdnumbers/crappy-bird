#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Wall : public sf::Drawable, public sf::Transformable
{
    public:
        Wall();
    private:
        sf::RectangleShape wallLower;
        sf::RectangleShape wallUpper;
};

#endif
