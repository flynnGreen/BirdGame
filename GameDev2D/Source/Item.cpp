#include "Item.h"

namespace GameDev2D
{
	Item::Item(unsigned char row, unsigned char col, bool hasCollider) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Item");
		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	Item::~Item()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type Item::GetType()
	{
		return Tile::Item;
	}

	void Item::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}
}