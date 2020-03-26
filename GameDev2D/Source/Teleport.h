#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class Teleport : public Tile
	{
	public:
		Teleport(unsigned char row, unsigned char col, bool hasCollider);
		~Teleport();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		AnimatedSprite* m_Tile;
	};
}