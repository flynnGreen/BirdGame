#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class Tree : public Tile
	{
	public:
		Tree(unsigned char row, unsigned char col, bool hasCollider, bool hasVariant);
		~Tree();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		AnimatedSprite* m_Tile;
	};
}