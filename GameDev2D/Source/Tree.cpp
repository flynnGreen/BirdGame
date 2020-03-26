#include "Tree.h"

namespace GameDev2D
{
	GameDev2D::Tree::Tree(unsigned char row, unsigned char col, bool hasCollider, bool hasVariant) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr)
	{
		m_Tile = new AnimatedSprite("Assets");
		m_Tile->SetFrameSpeed(3.0f);
		if (hasVariant == true)
		{
			m_Tile->AddFrame("Tree Top1");
			m_Tile->AddFrame("Tree Top2");
			m_Tile->AddFrame("Tree Top3");
			m_Tile->AddFrame("Tree Top4");
		}
		else
		{
			m_Tile->AddFrame("Tree Bottom1");
			m_Tile->AddFrame("Tree Bottom2");
			m_Tile->AddFrame("Tree Bottom3");
			m_Tile->AddFrame("Tree Bottom4");
		}
		m_Tile->SetDoesLoop(true);

		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	GameDev2D::Tree::~Tree()
	{
		SafeDelete(m_Tile);
	}

	Tile::Type GameDev2D::Tree::GetType()
	{
		return Tile::Tree;
	}

	void Tree::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);
	}

}