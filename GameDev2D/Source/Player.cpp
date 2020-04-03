#include "Player.h"
#include "Level.h"
#include "Room.h"
#include "Tile.h"


namespace GameDev2D
{
	Player::Player(Level* level) : GameObject(),
		m_Level(level),
		m_Collider(nullptr),
		m_Idle(nullptr),
		m_Walk(nullptr),
		m_ActiveSprite(nullptr),
		m_State(Unknown),
		m_IsInAir(false)
	{
		m_Idle = new SpriteAtlas("Assets");
		m_Idle->UseFrame("Sprite");
		m_Idle->SetAnchor(0.5f, 0.5f);
		m_Idle->AttachTo(this);

		m_Walk = new AnimatedSprite("Assets");
		m_Walk->AddFrame("Sprite Move1");
		m_Walk->AddFrame("Sprite Move2");
		m_Walk->AddFrame("Sprite Move3");
		m_Walk->SetDoesLoop(true);
		m_Walk->SetAnchor(0.5f, 0.5f);
		m_Walk->SetFrameSpeed(PLAYER_WALK_ANIMATION_FRAMESPEED);
		m_Walk->AttachTo(this);

		CollisionFilter filter(PLAYER_COLLISION_FILTER, TILE_COLLISION_FILTER);
		m_Collider = AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Dynamic, filter);

		Reset();
	}

	Player::~Player()
	{
		SafeDelete(m_Idle);
		SafeDelete(m_Walk);
	}

	void Player::Update(double delta)
	{
		if (IsDead() == false)
		{
			float directionX = 0.0f;

			//Determine which direction the player is going
			if (IsKeyDown(Keyboard::Left) == true)
			{
				directionX -= 1.0f;
			}

			if (IsKeyDown(Keyboard::Right) == true)
			{
				directionX += 1.0f;
			}

			//Set the scale and state based on the direction
			if (directionX != 0.0f)
			{
				SetScaleX(directionX);
				SetState(Moving);
			}

			//Is the player moving?
			if (m_State == Moving)
			{
				if (IsKeyDown(Keyboard::Right) == false && IsKeyDown(Keyboard::Left) == false)
				{
					//If player isn't moving, set state to idle
					SetState(Idle);
				}
			}

			Vector2 acceleration = GRAVITY;
			float maxSpeedX = directionX * PLAYER_MAX_SPEED;
			float speedDifferenceX = maxSpeedX - m_LinearVelocity.x;

			//Calculate the acceleration along the x-axis
			if (speedDifferenceX != 0.0f)
			{
				acceleration.x = speedDifferenceX < 0.0f ? -PLAYER_ACCELERATION : PLAYER_ACCELERATION;

				if (m_IsInAir == true)
				{
					acceleration.x *= PLAYER_AIR_ACCELERATION_PCT;
				}
			}

			//Calculate the velocity increment
			Vector2 velocityIncrement = acceleration * delta;

			//Cap the velocity increment to not exceed the max speed
			if (fabsf(velocityIncrement.x) > fabsf(speedDifferenceX))
			{
				velocityIncrement.x = speedDifferenceX;
			}

			//Increment the velocity
			Vector2 previousVelocity = m_LinearVelocity;
			m_LinearVelocity += velocityIncrement;

			//Cap the velocity on the y-axis
			if (m_LinearVelocity.y < GRAVITY.y)
			{
				m_LinearVelocity.y = GRAVITY.y;
			}

			//Increment the position
			Vector2 increment = (previousVelocity + m_LinearVelocity) * delta * 0.5;
			Vector2 position = GetPosition() + increment;

			//Clamp the position
			position.x = Math::Clamp(position.x, PLAYER_HALF_WIDTH, m_Level->GetActiveRoom()->GetWidth());
			position.y = Math::Clamp(position.y, -PLAYER_HALF_HEIGHT, m_Level->GetActiveRoom()->GetHeight());

			//Set the position
			SetPosition(position);

			//If the player is below zero, then change the state to Dead
			if (position.y <= 0.0f)
			{
				SetState(Dead);
			}

			//Set this to true, in case the player walks off the edge of a platform,
			//If the player doesn't, then they will collide with the ground and this will be
			//set back to false
			m_IsInAir = true;
		}
		else
		{
			Reset();
			m_Level->Reset();

		}
	}

	void Player::Draw(SpriteBatch* spriteBatch)
	{
		if (IsDead() == false)
		{
			spriteBatch->Draw(m_ActiveSprite);
		}
	}

	void Player::Reset()
	{
		//Determine the Player's spawn position based on what room they are in
		int activeIndex = m_Level->GetActiveRoomNum();
		Vector2 spawnPosition = Vector2(PLAYER_SPAWN_X[activeIndex], PLAYER_SPAWN_Y[activeIndex]);
		SetPosition(spawnPosition);

		//Reset the rest of the Player's members
		SetLinearVelocity(Vector2::Zero);
		m_IsInAir = true;
		SetState(Idle);
	}

	void Player::GetActiveRoom(int room)
	{

	}

	void Player::CollisionDetected(CollisionEvent* collisionEvent)
	{
		//Collider A is the Player
		if (collisionEvent->a->GetGameObject() == this)
		{
			//Collider B is a Tile
			if (collisionEvent->b->GetFilter().categoryBits == TILE_COLLISION_FILTER)
			{
				Tile* tile = static_cast<Tile*>(collisionEvent->b->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				collisionEvent->resolveCollision = HandleTileCollision(tile, playerEdgeCollision);
			}
		}
		//Collider B is the Player
		else if (collisionEvent->b->GetGameObject() == this)
		{
			//Collider A is a Tile
			if (collisionEvent->a->GetFilter().categoryBits == TILE_COLLISION_FILTER)
			{
				Tile* tile = static_cast<Tile*>(collisionEvent->a->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				collisionEvent->resolveCollision = HandleTileCollision(tile, playerEdgeCollision);
			}
		}
	}

	void Player::HandleKeyPress(Keyboard::Key key)
	{
		if (key == Keyboard::Spacebar)
		{
			if (m_IsInAir == false)
			{
				m_LinearVelocity.y += PLAYER_JUMP_SPEED;
				m_IsInAir = true;
			}
		}
	}

	void Player::HandleKeyReleased(Keyboard::Key key)
	{
		if (key == Keyboard::Spacebar)
		{
			if (m_LinearVelocity.y > 0.0f)
			{
				m_LinearVelocity.y *= 0.5f;
			}
		}
	}

	float Player::GetWidth()
	{
		return PLAYER_WIDTH;
	}

	float Player::GetHeight()
	{
		return PLAYER_HEIGHT;
	}

	void Player::SetState(State state)
	{
		//Ensure the previous state isn't being set, 
		//this prevents unnecessary state change
		if (state != m_State)
		{
			//Set the State
			m_State = state;

			//Idle State
			if (m_State == Idle)
			{
				m_ActiveSprite = m_Idle;
			}
			//Moving State
			else if (m_State == Moving)
			{
				m_Walk->SetFrameIndex(0);
				m_ActiveSprite = m_Walk;
			}
			//Dead State
			else if (m_State == Dead)
			{
				//TODO: Play sfx when player dies
			}
		}
	}

	bool Player::IsDead()
	{
		return m_State == Dead;
	}

	bool Player::HandleTileCollision(Tile* tile, unsigned char playerEdgeCollision)
	{
		bool resolveCollision = false;

		//Don't handle collision if the edge is unknown
		if (playerEdgeCollision == AxisAlignedRectangleCollider::UnknownEdge)
		{
			return resolveCollision;
		}

		//Bottom (of player) collision
		if ((playerEdgeCollision & AxisAlignedRectangleCollider::BottomEdge)
			== AxisAlignedRectangleCollider::BottomEdge)
		{
			m_IsInAir = false;
		}

		//The Tile type was the main tile we want to resolve the collision
		//so that the Player doesn't pass through the Tile
		if (tile->GetType() == Tile::Main || tile->GetType() == Tile::Item)
		{
			resolveCollision = true;
		}
		else if (tile->GetType() == Tile::Water)
		{
			SetState(Dead);
		}
		else if (tile->GetType() == Tile::Teleport)
		{
			if (IsKeyDown(Keyboard::Up))
			{
				//TODO: Doesn't work yet. Figure it out
				m_Level->SetActiveRoom(m_ActiveRoom++);
			}
		}

		return resolveCollision;
	}
}