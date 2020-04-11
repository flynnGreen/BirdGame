#pragma once

#include "Pickup.h"

namespace GameDev2D
{
	class MilletPickup : public Pickup
	{
	public:
		MilletPickup(const Vector2& startingPosition);
		~MilletPickup();

		Type GetType() override;

		void Draw(SpriteBatch* spriteBatch) override;

		float GetWidth() override;
		float GetHeight() override;

	private:
		SpriteAtlas* m_Millet;
	};
}