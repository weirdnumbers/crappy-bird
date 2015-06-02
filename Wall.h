#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Wall : public sf::Drawable, public sf::Transformable
{
    public:
        Wall();
        ~Wall();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::RectangleShape wallLower;
        sf::RectangleShape wallUpper;

        int gapHeight;
};

#endif
