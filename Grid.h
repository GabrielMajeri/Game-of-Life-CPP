#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <Cell.h>
#include <vector>

class Grid
{
    public:
        const int WIDTH, HEIGHT;

        Grid(int width, int height);
        virtual ~Grid();

        void update();

        void render(sf::RenderWindow &w);

        int getNrOfNeighbours(const int x, const int y);

        void setAlive(const int x, const int y, const bool alive);

    private:
        std::vector<Cell> cells, nextState;
};

#endif // GRID_H
