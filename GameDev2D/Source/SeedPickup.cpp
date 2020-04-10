#include "SeedPickup.h"
#include "Constants.h"


namespace GameDev2D
{
	SeedPickup::SeedPickup(const Vector2& startingPosition) : Pickup(startingPosition),
		m_Seed(nullptr)
	{
		m_Seed = new SpriteAtlas("Assets");
		m_Seed->UseFrame("Seed");
		m_Seed->SetAnchor(0.5f, 0.5f);
		m_Seed->AttachTo(this);

		CollisionFilter filter(PICKUP_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		float radius = fmaxf(GetWidth(), GetHeight()) * 0.5f;
		AddCircleCollider(radius, Collider::Static, filter);
	}

	SeedPickup::~SeedPickup()
	{
		SafeDelete(m_Seed);
	}

	Pickup::Type SeedPickup::GetType()
	{
		return Pickup::Seed;
	}

	void SeedPickup::Draw(SpriteBatch* spriteBatch)
	{
		if (m_State == Pickup::Animating || m_State == Pickup::Showing)
		{
			spriteBatch->Draw(m_Seed);
		}
	}

	float SeedPickup::GetWidth()
	{
		return m_Seed->GetWidth();
	}

	float SeedPickup::GetHeight()
	{
		return m_Seed->GetHeight();
	}
}