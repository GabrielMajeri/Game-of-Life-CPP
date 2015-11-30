#include "Cell.h"

Cell::Cell(int x, int y)
: x(x), y(y)
{
    alive = false;

    shape.setSize(sf::Vector2f(SIZE, SIZE));
    shape.setFillColor(sf::Color(255, 255, 255));
}

void Cell::render(sf::RenderWindow &w)
{
    if(alive)
    {
        shape.setPosition(x, y);
        w.draw(shape);
    }
}

void Cell::setAlive(bool alive)
{
    this->alive = alive;
}

bool Cell::isAlive()
{
    return alive;
}

Cell::~Cell()
{}
