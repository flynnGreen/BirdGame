#include "Water.h"

namespace GameDev2D
{
	GameDev2D::Water::Water(unsigned char row, unsigned char col, bool hasCollider, bool hasVariant) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new AnimatedSprite("Assets");
		m_Tile->SetFrameSpeed(4.0f);
		if (hasVariant == true)
		{
			m_Tile->AddFrame("Water Block1");
			m_Tile->AddFrame("Water Block2");
			m_Tile->AddFrame("Water Block3");
		}
		else
		{
			m_Tile->AddFrame("Water Bottom1");
			m_Tile->AddFrame("Water Bottom2");
			m_Tile->AddFrame("Water Bottom3");
		}
		m_Tile->SetDoesLoop(true);

		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	GameDev2D::Water::~Water()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type GameDev2D::Water::GetType()
	{
		return Tile::Water;
	}

	void Water::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}

}