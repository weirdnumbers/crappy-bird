#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Bird : public sf::Drawable, public sf::Transformable
{
    public:
        Bird();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        sf::Vector2f getSize();
    private:
        sf::RectangleShape mShape;
};


#endif
