#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class EmptyTile : public Tile
	{
	public:
		EmptyTile(unsigned char row, unsigned char col);
		~EmptyTile();

		Tile::Type GetType() override;
	};
}