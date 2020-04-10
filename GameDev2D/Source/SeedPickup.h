#pragma once

#include "Pickup.h"

namespace GameDev2D
{
	class SeedPickup : public Pickup
	{
	public:
		SeedPickup(const Vector2& startingPosition);
		~SeedPickup();

		Type GetType() override;

		void Draw(SpriteBatch* spriteBatch) override;

		float GetWidth() override;
		float GetHeight() override;

	private:
		SpriteAtlas* m_Seed;
	};
}