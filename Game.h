#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Bird.h"
#include "Wall.h"

class Game
{
    public:
        Game();
        void run();
    private:
        void moveBird(float timedelta);
        void handleInput();
        void processEvents();
        void update(sf::Time elapsedTime);
        void render();

        sf::RenderWindow mWindow;
        Bird mBird;
        std::vector<Wall> walls;

        int wallDistance;
        int jumpVelocity;
        int gravity;
        float birdVelocity;
};

#endif // GAME_H
