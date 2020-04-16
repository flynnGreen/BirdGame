#pragma once

#include <GameDev2D.h>

namespace GameDev2D
{
	class Enemy : public GameObject
	{
	public:
		Enemy();
		virtual ~Enemy();

		enum Type
		{
			EyeFly = 0,
			SexyFish,
			NPCnormal,
			NPCgreta,
		};

		virtual Type GetType() = 0;

		virtual void Update(double delta) override;
		virtual void Draw(SpriteBatch* spriteBatch = nullptr) override;
		virtual void Reset() override;

		virtual void CollisionDetected(CollisionEvent* collisionEvent) override;
	};
}