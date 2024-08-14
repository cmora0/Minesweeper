#include "Game.h"
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TextureManager.h"

// Reads in the config to set up the number of rows, columns, and mines.
Game::Game()
{
	// Creating sprites for the buttons.
	_digits.setTexture(TextureManager::GetTexture("digits"));
	_faceHappy.setTexture(TextureManager::GetTexture("face_happy"));
	_faceLose.setTexture(TextureManager::GetTexture("face_lose"));
	_faceWin.setTexture(TextureManager::GetTexture("face_win"));
	_debug.setTexture(TextureManager::GetTexture("debug"));
	_test1.setTexture(TextureManager::GetTexture("test_1"));
	_test2.setTexture(TextureManager::GetTexture("test_2"));
	_test3.setTexture(TextureManager::GetTexture("test_3"));

	// Reading from the config file.
	std::ifstream configFile("boards/config.cfg");
	if (configFile.is_open())
	{
		configFile >> _numColumns >> _numRows >> _numMines;
		configFile.close();
	}
	else
	{
		std::cout << "Could not open config file!" << std::endl;
	}
}

// Starts a game.
void Game::Initialize()
{
	std::ifstream configFile("boards/config.cfg");
	if (configFile.is_open())
	{
		configFile >> _numColumns >> _numRows >> _numMines;
		configFile.close();
	}
	else
	{
		std::cout << "Could not open config file!" << std::endl;
	}

	// Resizes the grid of tiles.
	_grid.resize(_numRows, std::vector<Tile>(_numColumns));

	// Randomly distributes mines among the grid of tiles.
	for (int i = 0; i < _numMines; ++i) {
		int randomRow = Random::Int(0, _numRows - 1);
		int randomCol = Random::Int(0, _numColumns - 1);

		// Makes sure the selected tile doesn't already have a mine by checking that tile's isMine status.
		while (_grid[randomRow][randomCol].GetMineStatus()) {
			randomRow = Random::Int(0, _numRows - 1);
			randomCol = Random::Int(0, _numColumns - 1);
		}

		_grid[randomRow][randomCol].SetMine();
	}

	// Calculates the number of adjacent mines.
	for (int row = 0; row < _numRows; ++row) {
		for (int col = 0; col < _numColumns; ++col) {
			Tile& currentTile = _grid[row][col];

			if (!currentTile.GetMineStatus()) {
				int numAdjacentMines = 0;

				// Loops through neighboring tiles.
				for (int xOffset = -1; xOffset <= 1; ++xOffset) {
					for (int yOffset = -1; yOffset <= 1; ++yOffset) {
						int neighborRow = row + yOffset;
						int neighborCol = col + xOffset;

						if (neighborRow >= 0 && neighborRow < _numRows && neighborCol >= 0 && neighborCol < _numColumns) {
							if (_grid[neighborRow][neighborCol].GetMineStatus()) {
								++numAdjacentMines;
							}
						}
					}
				}

				// Sets the adjacent mine count for the current tile.
				currentTile.SetNumAdjacent(numAdjacentMines);
			}
		}
	}
}

// Renders the game window and the grid of tiles.
void Game::Render(sf::RenderWindow& window)
{
	// Loops through the grid and render each tile.
	for (int row = 0; row < _numRows; ++row) {
		for (int col = 0; col < _numColumns; ++col) {
			Tile& currentTile = _grid[row][col];
			sf::Sprite& tileSprite = currentTile.GetSprite();

			// Creates a background sprite.
			sf::Sprite& backgroundSprite = currentTile.GetBackground();

			// Calculates the position of the current tile.
			float xPosition = col * 32.0f;
			float yPosition = row * 32.0f;

			// Sets the position of the tile sprite and its background.
			backgroundSprite.setPosition(xPosition, yPosition);
			tileSprite.setPosition(xPosition, yPosition);

			// Renders the background tile.
			window.draw(backgroundSprite);

			// Renders the tile sprite.
			window.draw(tileSprite);
		}
	}
}

// Handles the mouse inputs for the game.
void Game::HandleInput(sf::RenderWindow& window)
{
	// Checks if the left mouse button is pressed.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Gets the mouse position.
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		int row = mousePosition.y / _grid[0][0].GetSprite().getTextureRect().height;
		int col = mousePosition.x / _grid[0][0].GetSprite().getTextureRect().width;

		// Checks if the calculated indices are within the grid bounds.
		if (row >= 0 && row < _numRows && col >= 0 && col < _numColumns)
		{
			// Gets the tile at the clicked position.
			Tile& clickedTile = _grid[row][col];

			float x = static_cast<float>(mousePosition.x);
			float y = static_cast<float>(mousePosition.y);

			// Checks if the tile at clicked row and column contains the mouse click location.
			if (clickedTile.Contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))
				&& !clickedTile.GetRevealStatus() && !clickedTile.GetMineStatus() && !clickedTile.GetFlagStatus())
			{
				// Reveals the clicked tile and its neighbors if applicable.
				RevealTileAndNeighbors(row, col);

				// Renders the updated grid.
				Render(window);
			}
		}
	}

	// Checks if the right mouse button is pressed.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		// Gets the mouse position.
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		int row = mousePosition.y / _grid[0][0].GetSprite().getTextureRect().height;
		int col = mousePosition.x / _grid[0][0].GetSprite().getTextureRect().width;

		// Checks if the calculated indices are within the grid bounds
		if (row >= 0 && row < _numRows && col >= 0 && col < _numColumns)
		{
			// Gets the tile at the clicked position.
			Tile& clickedTile = _grid[row][col];

			// Checks if the tile at clicked row and column contains the mouse click location.
			if (clickedTile.Contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))
				&& !clickedTile.GetRevealStatus())
			{
				// Toggles the flag status.
				clickedTile.SetFlag();

				// Renders the updated grid.
				Render(window);
			}
		}
	}
}

// Reveals the clicked on tile and its neighbors if applicable.
void Game::RevealTileAndNeighbors(int row, int col)
{
	// Gets the current tile being processed.
	Tile& currentTile = _grid[row][col];

	// Reveals the current tile.
	currentTile.Reveal();

	// If the tile has zero adjacent mines, this reveals its neighbors.
	if (currentTile.GetNumAdjacent() == 0)
	{
		// Loops through neighboring tiles
		for (int yOffset = -1; yOffset <= 1; ++yOffset)
		{
			for (int xOffset = -1; xOffset <= 1; ++xOffset)
			{
				// Calculates the row and column indices of the neighbor tile.
				int newRow = row + yOffset;
				int newCol = col + xOffset;

				// Checks if the new indices are within the grid bounds.
				if (newRow >= 0 && newRow < _numRows && newCol >= 0 && newCol < _numColumns)
				{
					// Gets the neighbor tile
					Tile& neighborTile = _grid[newRow][newCol];

					// Checks if the neighboring tile is unrevealed.
					if (!neighborTile.GetRevealStatus())
					{
						// Recursively reveal the neighbor tile and its neighbors.
						RevealTileAndNeighbors(newRow, newCol);
					}
				}
			}
		}
	}
}