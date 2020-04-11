#include "EggPickup.h"
#include "Constants.h"

namespace GameDev2D
{
	EggPickup::EggPickup(const Vector2& startingPosition) : Pickup(startingPosition),
		m_Egg(nullptr)
	{
		m_Egg = new SpriteAtlas("Assets");
		m_Egg->UseFrame("Egg");
		m_Egg->SetAnchor(0.5f, 0.5f);
		m_Egg->AttachTo(this);

		CollisionFilter filter(PICKUP_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		float radius = fmaxf(GetWidth(), GetHeight()) * 0.5f;
		AddCircleCollider(radius, Collider::Static, filter);
	}

	EggPickup::~EggPickup()
	{
		SafeDelete(m_Egg);
	}

	Pickup::Type EggPickup::GetType()
	{
		return Pickup::Egg;
	}

	void EggPickup::Draw(SpriteBatch* spriteBatch)
	{
		if (m_State == Pickup::Animating || m_State == Pickup::Showing)
		{
			spriteBatch->Draw(m_Egg);
		}
	}

	float EggPickup::GetWidth()
	{
		return m_Egg->GetWidth();
	}

	float EggPickup::GetHeight()
	{
		return m_Egg->GetHeight();
	}
}