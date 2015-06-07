#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <deque>
#include "Bird.h"
#include "Wall.h"
#include "texture_manager.hpp"

class Game
{
    public:
        Game();
        void run();
    private:
        void restart();
        void moveBird(float timedelta);
        void moveWalls(float timedelta);
        void handleInput();
        void handleCollisions();
        void checkBirdBounds();
        void processEvents();
        void update(sf::Time elapsedTime);
        void render();
        void loadTextures();

        TextureManager textureManager;
        sf::RenderWindow mWindow;
        Bird mBird;
        std::deque<Wall> walls;

        int wallSpeed;
        int wallDistance;
        int jumpVelocity;
        int gravity;
        float birdVelocity;
        bool wasPressed;
        bool isPressed;
        bool paused;
};

#endif // GAME_H
