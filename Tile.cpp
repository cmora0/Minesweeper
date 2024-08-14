#include "Tile.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

Tile::Tile()
{
	// Creating sprites for all tile states.
	_tileHidden.setTexture(TextureManager::GetTexture("tile_Hidden"));
	_tileRevealed.setTexture(TextureManager::GetTexture("tile_revealed"));
	_tileMine.setTexture(TextureManager::GetTexture("mine"));
	_tileFlag.setTexture(TextureManager::GetTexture("flag"));
	_tile1.setTexture(TextureManager::GetTexture("number_1"));
	_tile2.setTexture(TextureManager::GetTexture("number_2"));
	_tile3.setTexture(TextureManager::GetTexture("number_3"));
	_tile4.setTexture(TextureManager::GetTexture("number_4"));
	_tile5.setTexture(TextureManager::GetTexture("number_5"));
	_tile6.setTexture(TextureManager::GetTexture("number_6"));
	_tile7.setTexture(TextureManager::GetTexture("number_7"));
	_tile8.setTexture(TextureManager::GetTexture("number_8"));

	// Initializing some tile variables.
	_isMine = false;
	_isFlagged = false;
	_isRevealed = false;
	_numAdjacent = 0;
}

sf::Sprite& Tile::GetSprite()
{
	// These if statements return specific sprites depending on the status of each tile.
	if (!_isRevealed && !_isFlagged)
	{
		return _tileHidden;
	}
	else if (!_isRevealed && _isFlagged)
	{
		return _tileFlag;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 0))
	{
		return _tileRevealed;
	}
	else if (_isRevealed && _isMine)
	{
		return _tileMine;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 1))
	{
		return _tile1;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 2))
	{
		return _tile2;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 3))
	{
		return _tile3;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 4))
	{
		return _tile4;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 5))
	{
		return _tile5;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 6))
	{
		return _tile6;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 7))
	{
		return _tile7;
	}
	else if (_isRevealed && !_isMine && (_numAdjacent == 8))
	{
		return _tile8;
	}
}

sf::Sprite& Tile::GetBackground()
{
	return _tileRevealed;
}

void Tile::SetMine()
{
	_isMine = !_isMine;
}

void Tile::SetFlag()
{
	_isFlagged = !_isFlagged;
}

void Tile::Reveal()
{
	_isRevealed = !_isRevealed;
}

void Tile::ClearTile()
{
	_isMine = false;
	_isFlagged = false;
	_isRevealed = false;
}

void Tile::SetPosition(float x, float y)
{
	GetSprite().setPosition(x, y);
}

void Tile::SetNumAdjacent(int num)
{
	_numAdjacent = num;
}

bool Tile::GetMineStatus()
{
	return _isMine;
}

bool Tile::GetFlagStatus()
{
	return _isFlagged;
}

bool Tile::GetRevealStatus()
{
	return _isRevealed;
}

bool Tile::Contains(float x, float y)
{
	return this->GetSprite().getGlobalBounds().contains(x, y);
}

int Tile::GetNumAdjacent()
{
	return _numAdjacent;
}