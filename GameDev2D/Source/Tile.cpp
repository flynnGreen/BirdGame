#include "Tile.h"
#include "Constants.h"


namespace GameDev2D
{
	Tile::Tile(unsigned char row, unsigned char col, bool hasCollider) : GameObject(),
		m_Row(row),
		m_Column(col)
	{
		//Calculate and set the position for each Tile
		float x = m_Column * TILE_SIZE + HALF_TILE_SIZE;
		float y = m_Row * TILE_SIZE + HALF_TILE_SIZE;
		SetPosition(x, y);

		//Is there a collider?
		if (hasCollider == true)
		{
			CollisionFilter filter(TILE_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
			AddAxisAlignedRectangleCollider(TILE_SIZE, TILE_SIZE, Collider::Static, filter);
		}
	}

	Tile::~Tile()
	{
	}

	void Tile::Update(double delta)
	{
	}

	void Tile::Draw(SpriteBatch* spriteBatch)
	{
	}

	void Tile::Reset()
	{
	}

	unsigned char Tile::GetRow()
	{
		return m_Row;
	}

	unsigned char Tile::GetColumn()
	{
		return m_Column;
	}
}