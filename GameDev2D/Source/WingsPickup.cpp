#include "WingsPickup.h"
#include "Constants.h"

namespace GameDev2D
{
	WingsPickup::WingsPickup(const Vector2& startingPosition) : Pickup(startingPosition),
		m_Wings(nullptr)
	{
		m_Wings = new SpriteAtlas("Assets");
		m_Wings->UseFrame("Wings");
		m_Wings->SetAnchor(0.5f, 0.5f);
		m_Wings->AttachTo(this);

		CollisionFilter filter(PICKUP_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		float radius = fmaxf(GetWidth(), GetHeight()) * 0.5f;
		AddCircleCollider(radius, Collider::Static, filter);
	}

	WingsPickup::~WingsPickup()
	{
		SafeDelete(m_Wings);
	}

	Pickup::Type WingsPickup::GetType()
	{
		return Pickup::Wings;
	}

	void WingsPickup::Draw(SpriteBatch* spriteBatch)
	{
		if (m_State == Pickup::Animating || m_State == Pickup::Showing)
		{
			spriteBatch->Draw(m_Wings);
		}
	}

	float WingsPickup::GetWidth()
	{
		return m_Wings->GetWidth();
	}

	float WingsPickup::GetHeight()
	{
		return m_Wings->GetHeight();
	}
}