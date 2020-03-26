#pragma once

#include "Tile.h"

namespace GameDev2D
{
	class MainTile : public Tile
	{
	public:
		MainTile(unsigned char row, unsigned char col, bool hasCollider, bool hasVariant);
		~MainTile();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		SpriteAtlas* m_Tile;
	};
}