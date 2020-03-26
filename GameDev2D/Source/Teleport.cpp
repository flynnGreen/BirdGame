#include "Teleport.h"

namespace GameDev2D
{
	GameDev2D::Teleport::Teleport(unsigned char row, unsigned char col, bool hasCollider) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new AnimatedSprite("Assets");
		m_Tile->SetFrameSpeed(4.0f);
		m_Tile->AddFrame("Teleporter1");
		m_Tile->AddFrame("Teleporter2");
		m_Tile->AddFrame("Teleporter3");
		m_Tile->AddFrame("Teleporter4");
		m_Tile->SetDoesLoop(true);

		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	GameDev2D::Teleport::~Teleport()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type GameDev2D::Teleport::GetType()
	{
		return Tile::Teleport;
	}

	void Teleport::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}

}