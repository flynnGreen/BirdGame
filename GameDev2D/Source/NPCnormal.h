#pragma once

#include "Enemy.h"
#include "Timer.h"

namespace GameDev2D
{
	class NPCnormal : public Enemy
	{
	public:
		NPCnormal(const Vector2& startingPosition);
		~NPCnormal();

		Enemy::Type GetType() override;

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch) override;
		void Reset() override;

		float GetWidth();
		float GetHeight();

	private:
		void Flip();

		//Member variables
		SpriteAtlas* m_NPC;
		Vector2 m_StartingPosition;
		float m_InitialDirectionX = 1.0f;
		Timer m_ChangedDirectionTimer;
	};
}