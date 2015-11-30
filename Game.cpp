#include "Game.h"

Game::Game()
: w(sf::VideoMode(Cell::SIZE * WIDTH, Cell::SIZE * HEIGHT), "Game of Life"), grid(WIDTH, HEIGHT)
{
    w.setFramerateLimit(60);

    font.loadFromFile("arial.ttf");

    paused = true;
    pauseTimer = 0;

    textBackground.setSize(sf::Vector2f(140, 25));
    textBackground.setPosition(8, 13);
    textBackground.setFillColor(sf::Color::Black);

    pausedText.setPosition(10, 10);
    pausedText.setFont(font);
    pausedText.setCharacterSize(22);
    pausedText.setColor(sf::Color::White);
}

void Game::gameLoop()
{
    const sf::Time UPS = sf::seconds(1.f/5.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(w.isOpen())
    {
        // Handle user input
        sf::Event event;
        while(w.pollEvent(event))
        {
            // Close the window after pressing the 'X' button
            // or after pressing ESCAPE
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                w.close();

            // Decrement the pauseTimer
            if(pauseTimer > 0) pauseTimer--;
            // Toggle paused mode
            if(pauseTimer == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                paused = !paused, pauseTimer = 20;

            // Get mouse input
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == true)
            {
                // Transform screen coordinates to Grid coordinates
                unsigned x = sf::Mouse::getPosition(w).x/Cell::SIZE;
                unsigned y = sf::Mouse::getPosition(w).y/Cell::SIZE;
                if(0 < x && x < WIDTH && 0 < y && y < HEIGHT)
                    // drawing to grid
                    grid.setAlive(x, y, true);
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) == true)
            {
                unsigned x = sf::Mouse::getPosition(w).x/Cell::SIZE;
                unsigned y = sf::Mouse::getPosition(w).y/Cell::SIZE;
                if(0 < x && x < WIDTH && 0 < y && y < HEIGHT)
                    // erasing the grid
                    grid.setAlive(x, y, false);
            }
        }

        // Update the game state
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > UPS)
        {
            timeSinceLastUpdate -= UPS;

            if(!paused)
                grid.update();
        }

        // Render the game
        w.clear(sf::Color::Black);

        // Render the grid
        grid.render(w);

        // Draw the pause indicator
        w.draw(textBackground);
        pausedText.setString((paused == true ? "Paused: true":"Paused: false"));
        w.draw(pausedText);

        // Display buffer
        w.display();
    }
}

Game::~Game()
{}
