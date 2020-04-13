#pragma once

#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{
	class NPC : public Enemy
	{
	public:
		NPC(const Vector2& startingPosition, float displacementX);
		~NPC();

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
		SpriteAtlas* m_NPC;
		Vector2 m_StartingPosition;
		Vector2 m_EndPointRight;
		Vector2 m_EndPointLeft;
		float m_InitialDirectionX;
		Timer m_ChangedDirectionTimer;
	};
}