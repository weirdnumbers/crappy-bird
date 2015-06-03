#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <deque>
#include "Bird.h"
#include "Wall.h"

class Game
{
    public:
        Game();
        void run();
    private:
        void moveBird(float timedelta);
        void moveWalls(float timedelta);
        void handleInput();
        void processEvents();
        void update(sf::Time elapsedTime);
        void render();

        sf::RenderWindow mWindow;
        Bird mBird;
        std::deque<Wall> walls;
        //std::deque<Wall> walls;

        int wallSpeed;
        int wallDistance;
        int jumpVelocity;
        int gravity;
        float birdVelocity;
        bool wasPressed;
        bool isPressed;
};

#endif // GAME_H
