#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class Water : public Tile
	{
	public:
		Water(unsigned char row, unsigned char col, bool hasCollider);
		~Water();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		AnimatedSprite* m_Tile;
	};
}