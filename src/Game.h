#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Grid.h>

class Game
{
    public:
        Game();
        virtual ~Game();
        void gameLoop();


        /*
        * Game constants: width and height in TILES of the grid.
        */
        static const int WIDTH = 40;
        static const int HEIGHT = 34;

    private:
        /*
        * Game resources
        */
        sf::RenderWindow w;
        sf::Font font;
        Grid grid;

        sf::RectangleShape textBackground;
        sf::Text pausedText;

        bool paused;
        int pauseTimer;
};

#endif // GAME_H
