#include "Grid.h"

/*
* A grid represents all of the cells placed in a vector.
* The grid also calculates the next state.
*/
Grid::Grid(int width, int height)
: WIDTH(width), HEIGHT(height)
{
    for(int j = 0; j < HEIGHT; j++)
        for(int i = 0; i < WIDTH; i++)
            cells.push_back(Cell(i * Cell::SIZE, j * Cell::SIZE));

    for(int j = 0; j < HEIGHT; j++)
        for(int i = 0; i < WIDTH; i++)
            nextState.push_back(Cell(i * Cell::SIZE, j * Cell::SIZE));
}

// updates the game state
void Grid::update()
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
        {
            int n = getNrOfNeighbours(x, y);

            if(cells.at(x + y * WIDTH).isAlive())
                if(n == 2 || n == 3)
                    // if not under/over-populated, stay alive
                    nextState.at(x + y * WIDTH).setAlive(true);
                else
                    // if under/over-populated, die
                    nextState.at(x + y * WIDTH).setAlive(false);
            else
                if(n == 3)
                    // if enough cells are nearby to reproduce
                    nextState.at(x + y * WIDTH).setAlive(true);
                else
                    // if not enough/to many cells nearby
                    nextState.at(x + y * WIDTH).setAlive(false);
        }

    // copy next state to current state
    for(unsigned i = 0; i < cells.size(); ++i)
        cells.at(i).setAlive(nextState.at(i).isAlive());
}

// determines how many neighbours a cell has
// the borders of the screen are presumed dead
// the neighbours are searched diagonally, vertically and horizontally
int Grid::getNrOfNeighbours(const int x, const int y)
{
    int nr = 0;

    if(x > 0)
        if(cells.at(x-1 + y * WIDTH).isAlive())
            nr++;

    if(x > 0 && y > 0)
        if(cells.at(x-1 + (y-1)*WIDTH).isAlive())
            nr++;

    if(y > 0)
        if(cells.at(x + (y-1)*WIDTH).isAlive())
            nr++;

    if(y > 0 && x < WIDTH - 1)
        if(cells.at(x+1 + (y-1)*WIDTH).isAlive())
            nr++;

    if(x < WIDTH - 1)
        if(cells.at(x+1 + y * WIDTH).isAlive())
            nr++;

    if(x < WIDTH - 1 && y < HEIGHT - 1)
        if(cells.at(x+1 + (y+1) * WIDTH).isAlive())
            nr++;

    if(y < HEIGHT - 1)
        if(cells.at(x + (y+1) * WIDTH).isAlive())
            nr++;

    if(x > 0 && y < HEIGHT - 1)
        if(cells.at(x-1 + (y+1) * WIDTH).isAlive())
            nr++;

    return nr;
}

// draw the grid to screen
void Grid::render(sf::RenderWindow &w)
{
    for(unsigned i = 0; i < cells.size(); ++i)
        cells.at(i).render(w);

    sf::RectangleShape line;
    line.setFillColor(sf::Color(125, 125, 125));

    // vertical lines
    for(int i = 0; i < WIDTH; ++i)
    {
        line.setSize(sf::Vector2f(1, HEIGHT * Cell::SIZE));
        line.setPosition(i * Cell::SIZE, 0);
        w.draw(line);
    }

    // horizontal lines
    for(int j = 0; j < HEIGHT; ++j)
    {
        line.setSize(sf::Vector2f(WIDTH * Cell::SIZE, 1));
        line.setPosition(0, j * Cell::SIZE);
        w.draw(line);
    }
}

// sets the alive attribute of the indicated cell
void Grid::setAlive(int x, int y, bool alive)
{
    cells.at(x + y * WIDTH).setAlive(alive);
}

Grid::~Grid()
{}
