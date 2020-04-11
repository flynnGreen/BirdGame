#include "MilletPickup.h"
#include "Constants.h"

namespace GameDev2D
{
	MilletPickup::MilletPickup(const Vector2& startingPosition) : Pickup(startingPosition),
		m_Millet(nullptr)
	{
		m_Millet = new SpriteAtlas("Assets");
		m_Millet->UseFrame("Millet");
		m_Millet->SetAnchor(0.5f, 0.5f);
		m_Millet->AttachTo(this);

		CollisionFilter filter(PICKUP_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		float radius = fmaxf(GetWidth(), GetHeight()) * 0.5f;
		AddCircleCollider(radius, Collider::Static, filter);
	}

	MilletPickup::~MilletPickup()
	{
		SafeDelete(m_Millet);
	}

	Pickup::Type MilletPickup::GetType()
	{
		return Pickup::Millet;
	}

	void MilletPickup::Draw(SpriteBatch* spriteBatch)
	{
		if (m_State == Pickup::Animating || m_State == Pickup::Showing)
		{
			spriteBatch->Draw(m_Millet);
		}
	}

	float MilletPickup::GetWidth()
	{
		return m_Millet->GetWidth();
	}

	float MilletPickup::GetHeight()
	{
		return m_Millet->GetHeight();
	}
}