#pragma once

#include <GameDev2D.h>
#include "Constants.h"


namespace GameDev2D
{
	//Forward declarations
	class Level;
	class Tile;
	class Platform;
	class Spikes;

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

		void SetMusic(int roomNum);

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

		//Kills player
		void Kill();

		//Determines if a Player and Platform are colliding and collision should be resolved
		bool ValidatePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision);
		bool ValidateSpikesCollision(Spikes* spikes, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision);

	private:
		//Handle collision between a specific Tile and the Player
		bool HandleTileCollision(Tile* tile, unsigned char playerEdgeCollision);
		bool HandlePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision);
		bool HandleSpikesCollision(Spikes* spikes, unsigned char playerEdgeCollision, unsigned char spikesEdgeCollision);

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
		bool m_IsJokeOn;
		Audio* m_DeathSoundJ;
		Audio* m_JumpSoundJ;
		Audio* m_DeathSound;
		Audio* m_JumpSound;
		Audio* m_JumpSound2;
		Audio* m_JokeModeActivated;
		Audio* m_Birds;
		Audio* m_Music[LEVEL1_ROOM_NUM];
	};
}