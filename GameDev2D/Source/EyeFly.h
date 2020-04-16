#pragma once

#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{
	class EyeFly : public Enemy
	{
	public:
		EyeFly(const Vector2& startingPosition, float displacementY);
		~EyeFly();

		Enemy::Type GetType() override;

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth();
		float GetHeight();

	private:
		void Flip();

		//Member variables
		AnimatedSprite* m_EyeFly;
		Vector2 m_StartingPosition;
		Vector2 m_EndPointRight;
		Vector2 m_EndPointLeft;
		float m_InitialDirectionX;
	};
}