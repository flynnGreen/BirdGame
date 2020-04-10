#pragma once

#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{
	class SexyFish : public Enemy
	{
	public:
		SexyFish(const Vector2& startingPosition, float displacementX);
		~SexyFish();

		Enemy::Type GetType() override;

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		void CollisionDetected(CollisionEvent* collisionEvent) override;

		float GetWidth();
		float GetHeight();

	private:
		void Flip();

		//Member variables
		AnimatedSprite* m_SexyFish;
		Vector2 m_StartingPosition;
		Vector2 m_EndPointRight;
		Vector2 m_EndPointLeft;
		float m_InitialDirectionX;
		Timer m_ChangedDirectionTimer;
	};
}