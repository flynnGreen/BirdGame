#pragma once

#include "Pickup.h"

namespace GameDev2D
{
	class WingsPickup : public Pickup
	{
	public:
		WingsPickup(const Vector2& startingPosition);
		~WingsPickup();

		Type GetType() override;

		void Draw(SpriteBatch* spriteBatch) override;

		float GetWidth() override;
		float GetHeight() override;

	private:
		SpriteAtlas* m_Wings;
	};
}
