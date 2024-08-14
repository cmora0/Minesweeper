#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
	// Will hold the tile's sprites.
	sf::Sprite _tileHidden;
	sf::Sprite _tileRevealed;
	sf::Sprite _tileMine;
	sf::Sprite _tileFlag;
	sf::Sprite _tile1;
	sf::Sprite _tile2;
	sf::Sprite _tile3;
	sf::Sprite _tile4;
	sf::Sprite _tile5;
	sf::Sprite _tile6;
	sf::Sprite _tile7;
	sf::Sprite _tile8;

public:
	// Tile variables.
	bool _isMine;
	bool _isFlagged;
	bool _isRevealed;
	int _numAdjacent;
	
	// Will create a tile.
	Tile();
	sf::Sprite& GetSprite();
	
	// Function to get the background/revealed tile.
	sf::Sprite& GetBackground();

	// Tile functions.
	void SetMine();
	void SetFlag();
	void Reveal();
	void ClearTile();
    void SetPosition(float x, float y);
	void SetNumAdjacent(int num);
	bool GetMineStatus();
	bool GetFlagStatus();
	bool GetRevealStatus();
	bool Contains(float x, float y);
	int GetNumAdjacent();
};

