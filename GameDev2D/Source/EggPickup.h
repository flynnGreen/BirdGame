#pragma once

#include "Pickup.h"

namespace GameDev2D
{
	class EggPickup : public Pickup
	{
	public:
		EggPickup(const Vector2& startingPosition);
		~EggPickup();

		Type GetType() override;

		void Draw(SpriteBatch* spriteBatch) override;

		float GetWidth() override;
		float GetHeight() override;

	private:
		SpriteAtlas* m_Egg;
	};
}