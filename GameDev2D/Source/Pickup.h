#pragma once

#include <GameDev2D.h>
#include "Timer.h"

namespace GameDev2D
{
	class Pickup : public GameObject
	{
	public:
		Pickup(const Vector2& startingPosition);
		virtual ~Pickup();

		enum Type
		{
			Seed = 0,
			Millet,
			Egg,
			Wings,
		};

		virtual Type GetType() = 0;

		virtual void Update(double delta) override;
		virtual void Draw(SpriteBatch* spriteBatch) override;
		virtual void Reset() override;

		virtual float GetWidth() = 0;
		virtual float GetHeight() = 0;

		virtual void Present();
		virtual void Consume();

	protected:
		enum State
		{
			Hidden = 0,
			Animating,
			Showing,
			Consumed
		};

		Vector2 m_StartingPosition;
		Timer m_Timer;
		State m_State;
	};
}