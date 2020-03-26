#pragma once
#include "Tile.h"

namespace GameDev2D
{
	class House : public Tile
	{
	public:
		House(unsigned char row, unsigned char col, bool hasCollider);
		~House();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;

	private:
		SpriteAtlas* m_Tile;
	};
}