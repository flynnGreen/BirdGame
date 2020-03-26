#include "House.h"

namespace GameDev2D
{
	House::House(unsigned char row, unsigned char col, bool hasCollider) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("House");
		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	House::~House()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type House::GetType()
	{
		return Tile::House;
	}

	void House::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}
}