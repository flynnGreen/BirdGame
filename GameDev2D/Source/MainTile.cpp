#include "MainTile.h"

namespace GameDev2D
{
	MainTile::MainTile(unsigned char row, unsigned char col, bool hasCollider) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Tile");
		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	MainTile::~MainTile()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type MainTile::GetType()
	{
		return Tile::Main;
	}

	void MainTile::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}
}