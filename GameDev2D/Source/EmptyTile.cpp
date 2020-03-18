#include "EmptyTile.h"

namespace GameDev2D
{
	EmptyTile::EmptyTile(unsigned char row, unsigned char col) :
		Tile(row, col, false)
	{
	}

	EmptyTile::~EmptyTile()
	{
	}

	Tile::Type EmptyTile::GetType()
	{
		return Tile::Empty;
	}
}