#include <SFML/Graphics.hpp>
#include <iostream>
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
#include "Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");

    // Creates an instance of the Game class
    Game game;

    // Initializes the game
    game.Initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Makes the game work.
        game.HandleInput(window);

        window.clear();

        // Renders the game
        game.Render(window);

        window.display();
    }

    // Clears out any textures before the program ends
    TextureManager::Clear();

    return 0;
}