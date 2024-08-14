#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>

// The Game class stores the game's functionality and rendering.
class Game
{
	// Will hold the button sprites.
	sf::Sprite _digits;
	sf::Sprite _faceHappy;
	sf::Sprite _faceLose;
	sf::Sprite _faceWin;
	sf::Sprite _debug;
	sf::Sprite _test1;
	sf::Sprite _test2;
	sf::Sprite _test3;

	// The game needs columns, rows, mines, and a grid of tiles.
	int _numColumns;
	int _numRows;
	int _numMines;
	std::vector<std::vector<Tile>> _grid;
public:
	Game();
	void Initialize();
	void Render(sf::RenderWindow& window);
	void HandleInput(sf::RenderWindow& window);
	void RevealTileAndNeighbors(int row, int col);
};

