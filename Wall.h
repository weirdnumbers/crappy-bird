#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

class Wall : public sf::Drawable, public sf::Transformable
{
    public:
        Wall();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        int getWidth();
        sf::IntRect getLowerIntRect(const sf::Vector2f& position);
        sf::IntRect getUpperIntRect(const sf::Vector2f& position);
        sf::RectangleShape& getLowerWall();
        sf::RectangleShape& getUpperWall();
    private:
        int gapHeight;
        int wallWidth;
        int minHeight;

        sf::RectangleShape wallLower;
        sf::RectangleShape wallUpper;
};

#endif
