#pragma once

#include <GameDev2D.h>
#include "Constants.h"


namespace GameDev2D
{
	//Forward declarations
	class Level;
	class Tile;
	class Platform;

	//Class definitions
	class Player : public GameObject
	{
	public:
		Player(Level* level);
		~Player();

		void Update(double delta) override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;
		void Reset() override;

		void CollisionDetected(CollisionEvent* collisionEvent) override;

		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);

		float GetWidth();
		float GetHeight();

		AxisAlignedRectangleCollider* GetCollider();

		//State enum to manage the state of the player
		enum State
		{
			Idle = 0,
			Moving,
			Dead,
			Unknown
		};

		//Sets the state of the Player
		void SetState(State state);

		//Returns wether the player is dead or not
		bool IsDead();

		//Determines if a Player and Platform are colliding and collision should be resolved
		bool ValidatePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision);

	private:
		//Handle collision between a specific Tile and the Player
		bool HandleTileCollision(Tile* tile, unsigned char playerEdgeCollision);
		bool HandlePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision);

		//Member variables
		Level* m_Level;
		AxisAlignedRectangleCollider* m_Collider;
		SpriteAtlas* m_Idle;
		AnimatedSprite* m_Walk;
		Sprite* m_ActiveSprite;
		State m_State;
		int m_ActiveRoom = 0;
		bool m_IsInAir;
		bool m_CanDoubleJump;
		Vector2 m_PreviousPosition;
	};
}