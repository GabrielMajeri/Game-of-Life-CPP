#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell
{
    public:
        static const int SIZE = 16;

        Cell(int x, int y);

        virtual ~Cell();

        void render(sf::RenderWindow &w);

        void setAlive(bool alive);
        bool isAlive();

    private:
        const int x, y;
        bool alive;
        sf::RectangleShape shape;
};

#endif // CELL_H
