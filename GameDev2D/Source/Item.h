#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class Item : public Tile
	{
	public:
		Item(unsigned char row, unsigned char col, bool hasCollider);
		~Item();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		SpriteAtlas* m_Tile;
	};
}