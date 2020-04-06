#pragma once

#include <GameDev2D.h>
#include "Timer.h"
#include "Constants.h"


namespace GameDev2D
{
	class Room;

	class Platform : public GameObject
	{
	public:
		Platform(Room* room, Vector2 startPosition, Vector2 displacement, double duration);
		~Platform();

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;
		void Reset() override;

		float GetWidth();
		float GetHeight();

		AxisAlignedRectangleCollider* GetCollider();

		Vector2 GetPreviousPosition();

	private:
		Room* m_Room;
		SpriteAtlas* m_Segments[PLATFORM_NUM_SEGMENTS];
		AxisAlignedRectangleCollider* m_Collider;
		Vector2 m_StartPosition;
		Vector2 m_Displacement;
		Timer m_Timer;
		Vector2 m_PreviousPosition;
	};
}