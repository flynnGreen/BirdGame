#pragma once
#include <GameDev2D.h>
#include "Timer.h"
#include "Constants.h"

namespace GameDev2D
{
	class Room;

	class Spikes : public GameObject
	{
	public:
		Spikes(Room* room, Vector2 startPosition, Vector2 displacement, double duration);
		~Spikes();

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;
		void Reset() override;

		float GetWidth();
		float GetHeight();

		AxisAlignedRectangleCollider* GetCollider();

	private:
		Room* m_Room;
		AxisAlignedRectangleCollider* m_Collider;
		SpriteAtlas* m_Spikes;
		Vector2 m_StartPosition;
		Vector2 m_Displacement;
		Timer m_Timer;
	};
}