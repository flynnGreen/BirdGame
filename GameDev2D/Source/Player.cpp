#include "Player.h"
#include "Level.h"
#include "Room.h"
#include "Tile.h"
#include "Platform.h"
#include "Spikes.h"
#include "Enemy.h"
#include "Pickup.h"


namespace GameDev2D
{
	Player::Player(Level* level) : GameObject(),
		m_Level(level),
		m_Collider(nullptr),
		m_Idle(nullptr),
		m_Walk(nullptr),
		m_ActiveSprite(nullptr),
		m_State(Unknown),
		m_IsInAir(false),
		m_CanDoubleJump(true),
		m_PreviousPosition(Vector2::Zero),
		m_IsJokeOn(false),
		m_DeathSoundJ(nullptr),
		m_JumpSoundJ(nullptr),
		m_DeathSound(nullptr),
		m_JumpSound(nullptr),
		m_JumpSound2(nullptr),
		m_JokeModeActivated(nullptr),
		m_Birds(nullptr),
		m_Music { nullptr },
		m_Bonk(nullptr),
		m_ItemGet(nullptr),
		m_Inventory(nullptr),
		m_Dialogue(nullptr),
		m_Speaking(nullptr),
		m_SpeakingJ(nullptr),
		m_WinText(nullptr),
		m_Cheater(nullptr),
		m_WinMusic(nullptr)
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

		m_WinText = new AnimatedSprite("Assets");
		m_WinText->AddFrame("WinText1");
		m_WinText->AddFrame("WinText2");
		m_WinText->AddFrame("WinText3");
		m_WinText->SetDoesLoop(true);
		m_WinText->SetAnchor(0.5f, 0.5f);
		m_WinText->SetFrameSpeed(3);
		m_WinText->AttachTo(GetCamera());

		m_Cheater = new AnimatedSprite("Assets");
		m_Cheater->UseFrame("Cheater");
		m_Cheater->SetAnchor(0.5f, 0.5f);
		m_Cheater->AttachTo(GetCamera());

		m_DeathSoundJ = new Audio("Death");
		m_JumpSoundJ = new Audio("Jump");
		m_DeathSound = new Audio("DeathReal");
		m_JumpSound = new Audio("JumpReal");
		m_JumpSound2 = new Audio("JumpReal2");
		m_JokeModeActivated = new Audio("JokeModeActivated");
		m_Birds = new Audio("Birdsong");
		m_Bonk = new Audio("Bonk");
		m_ItemGet = new Audio("ItemGet");
		m_WinMusic = new Audio("WinMusic");
		m_Speaking = new Audio("Speaking");
		m_SpeakingJ = new Audio("JokeSpeaking");

		m_Inventory = new SpriteFont("Hanged Letters_32");
		m_Inventory->SetColor(Color::OrangeColor());
		m_Inventory->SetText("Seeds: 0\nMillet: 0\nEggs: 0");
		m_Inventory->SetAnchor(4, -1.6);
		m_Inventory->AttachTo(GetCamera());

		m_Dialogue = new SpriteFont("OpenSans-CondBold_22");
		m_Dialogue->SetColor(Color::WhiteColor());
		m_Dialogue->SetText(INTRO_TEXT);
		m_Dialogue->SetAnchor(0.5, 0.5);
		m_Dialogue->AttachTo(GetCamera());

		CollisionFilter filter(PLAYER_COLLISION_FILTER, TILE_COLLISION_FILTER | PLATFORM_COLLISION_FILTER | SPIKES_COLLISION_FILTER | ENEMY_COLLISION_FILTER | PICKUP_COLLISION_FILTER);
		m_Collider = AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Dynamic, filter);

		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Music[i] = new Audio(LEVEL1_MUSIC[i]);
			m_Music[i]->SetDoesLoop(true);
		}

		m_Level->Reset();
	}

	Player::~Player()
	{
		UnloadAudio("Death");
		UnloadAudio("Jump");
		UnloadAudio("JumpReal");
		UnloadAudio("JumpReal2");
		UnloadAudio("DeathReal");
		UnloadAudio("JokeModeActivated");
		UnloadAudio("Birdsong");
		UnloadAudio("Room1Music");
		UnloadAudio("Room2Music");
		UnloadAudio("Room3Music");
		UnloadAudio("WinMusic");
		UnloadAudio("Bonk");
		UnloadAudio("ItemGet");
		UnloadAudio("Speaking");
		UnloadAudio("JokeSpeaking");
		UnloadFont("Hanged Letters_32");
		UnloadFont("OpenSans-CondBold_22");

		SafeDelete(m_Birds);
		SafeDelete(m_JokeModeActivated);
		SafeDelete(m_DeathSound);
		SafeDelete(m_JumpSound);
		SafeDelete(m_JumpSound2);
		SafeDelete(m_DeathSoundJ);
		SafeDelete(m_JumpSoundJ);
		SafeDelete(m_Idle);
		SafeDelete(m_Walk);
		SafeDelete(m_Inventory);
		SafeDelete(m_Bonk);
		SafeDelete(m_ItemGet);
		SafeDelete(m_Dialogue);
		SafeDelete(m_WinMusic);
		SafeDelete(m_WinText);
		SafeDelete(m_Cheater);
		SafeDelete(m_Speaking);
		SafeDelete(m_SpeakingJ);

		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			SafeDelete(m_Music[i]);
		}
	}

	void Player::Update(double delta)
	{
		if (IsDead() == false)
		{
			if (m_GotWings == false)
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

				//Cache the player's previous position
				m_PreviousPosition = GetPosition();

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

				if (IsKeyDown(Keyboard::Spacebar) || IsKeyDown(Keyboard::Left) || IsKeyDown(Keyboard::Right))
				{
					m_IsSpeaking = false;
				}
			}
		}

		std::string inventory = "Seeds: " + std::to_string(m_SeedAmt);
		inventory.append("\nMillet: " + std::to_string(m_MilletAmt));
		inventory.append("\nEggs: " + std::to_string(m_EggAmt));

		m_Inventory->SetText(inventory);
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
		m_PreviousPosition = Vector2::Zero;
		SetScaleX(1.0);
		m_CanDoubleJump = true;
		//m_IsSpeaking = false;

		m_Birds->Stop();
		m_Birds->Play();

		SetMusic(m_Level->GetActiveRoomNum());

		m_ActiveRoom = m_Level->GetActiveRoomNum();
	}

	void Player::DrawHUD()
	{
		if (m_IsSpeaking == true)
		{
			m_Dialogue->Draw();
		}

		if (m_GotWings == true)
		{
			if (m_MilletAmt < MILLET_REQUIRED)
			{
				m_Cheater->Draw();
			}
			else
			{
				m_WinText->Draw();
			}
		}

		m_Inventory->Draw();
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
			//Collider B is a Platform
			else if (collisionEvent->b->GetFilter().categoryBits == PLATFORM_COLLISION_FILTER)
			{
				Platform* platform = static_cast<Platform*>(collisionEvent->b->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				unsigned char platformEdgeCollision = platform->GetCollider()->GetEdgeCollision();
				collisionEvent->resolveCollision = HandlePlatformCollision(platform, playerEdgeCollision, platformEdgeCollision);
			}
			//Collider B is Spikes
			else if (collisionEvent->b->GetFilter().categoryBits == SPIKES_COLLISION_FILTER)
			{
				Spikes* spikes = static_cast<Spikes*>(collisionEvent->b->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				unsigned char spikesEdgeCollision = spikes->GetCollider()->GetEdgeCollision();
				HandleSpikesCollision(spikes);
			}
			//Collider B is an Enemy
			else if (collisionEvent->b->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->b->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				HandleEnemyCollision(enemy, playerEdgeCollision);
			}
			//Collider B is a Pickup
			else if (collisionEvent->b->GetFilter().categoryBits == PICKUP_COLLISION_FILTER)
			{
				Pickup* pickup = static_cast<Pickup*>(collisionEvent->b->GetGameObject());
				HandlePickupCollision(pickup);
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
			//Collider A is a Platform
			else if (collisionEvent->a->GetFilter().categoryBits == PLATFORM_COLLISION_FILTER)
			{
				Platform* platform = static_cast<Platform*>(collisionEvent->a->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				unsigned char platformEdgeCollision = platform->GetCollider()->GetEdgeCollision();
				collisionEvent->resolveCollision = HandlePlatformCollision(platform, playerEdgeCollision, platformEdgeCollision);
			}
			//Collider A is Spikes
			else if (collisionEvent->a->GetFilter().categoryBits == SPIKES_COLLISION_FILTER)
			{
				Spikes* spikes = static_cast<Spikes*>(collisionEvent->a->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				unsigned char spikesEdgeCollision = spikes->GetCollider()->GetEdgeCollision();
				HandleSpikesCollision(spikes);
			}
			//Collider A is an Enemy
			else if (collisionEvent->a->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->a->GetGameObject());
				unsigned char playerEdgeCollision = m_Collider->GetEdgeCollision();
				HandleEnemyCollision(enemy, playerEdgeCollision);
			}
			//Collider A is a Pickup
			else if (collisionEvent->a->GetFilter().categoryBits == PICKUP_COLLISION_FILTER)
			{
				Pickup* pickup = static_cast<Pickup*>(collisionEvent->a->GetGameObject());
				HandlePickupCollision(pickup);
			}
		}
	}

	void Player::HandleKeyPress(Keyboard::Key key)
	{
		//Set Joke mode
		if (key == Keyboard::J)
		{
			if (m_IsJokeOn == false)
			{
				m_IsJokeOn = true;
				m_JokeModeActivated->Stop();
				m_JokeModeActivated->Play();
			}
			else if (m_IsJokeOn == true)
			{
				m_IsJokeOn = false;
				m_JokeModeActivated->Stop();
			}
		}

		if (key == Keyboard::Spacebar)
		{
			if (m_IsInAir == false)
			{
				m_LinearVelocity.y += PLAYER_JUMP_SPEED;
				m_IsInAir = true;

				if (m_IsJokeOn == true)
				{
					m_JumpSoundJ->Stop();
					m_JumpSoundJ->Play();
				}
				else
				{
					m_JumpSound->Stop();
					m_JumpSound->Play();
				}
			}
			else
			{
				if (m_CanDoubleJump == true)
				{
					m_LinearVelocity.y = PLAYER_JUMP_SPEED;
					m_CanDoubleJump = false;
					if (m_IsJokeOn == true)
					{
						m_JumpSoundJ->Stop();
						m_JumpSoundJ->Play();
					}
					else
					{
						m_JumpSound2->Stop();
						m_JumpSound2->Play();
					}
				}
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

	void Player::SetMusic(int roomNum)
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Music[i]->Stop();
		}
		m_Music[roomNum]->Play();
	}

	AxisAlignedRectangleCollider* Player::GetCollider()
	{
		return m_Collider;
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
				if (m_IsJokeOn == true)
				{
					m_DeathSoundJ->Stop();
					m_DeathSoundJ->Play();
				}
				else
				{
					m_DeathSound->Stop();
					m_DeathSound->Play();
				}
			}
		}
	}

	bool Player::IsDead()
	{
		return m_State == Dead;
	}

	void Player::Kill()
	{
		SetState(Dead);
	}

	bool Player::ValidatePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision)
	{
		//Local variables
		float previousPlayerBottomEdge = m_PreviousPosition.y - PLAYER_HALF_HEIGHT;
		float playerBottomEdge = GetPosition().y - PLAYER_HALF_HEIGHT;
		float previousPlatformTopEdge = platform->GetPreviousPosition().y + PLATFORM_SEGMENT_HEIGHT * 0.5f;
		float platformTopEdge = platform->GetPosition().y + PLATFORM_SEGMENT_HEIGHT * 0.5f;

		if (GetLinearVelocity().y <= 0.0f && IsKeyDown(Keyboard::Down) == false)
		{
			if (Math::IsClose(playerBottomEdge, platformTopEdge, 2.5f)
				|| Math::IsClose(previousPlayerBottomEdge, previousPlatformTopEdge, 2.5f)
				|| (previousPlayerBottomEdge > platformTopEdge && playerBottomEdge < platformTopEdge)
				|| previousPlayerBottomEdge == platformTopEdge
				|| previousPlayerBottomEdge == previousPlatformTopEdge
)
			{
				if ((playerEdgeCollision & AxisAlignedRectangleCollider::BottomEdge) == AxisAlignedRectangleCollider::BottomEdge
					&& (platformEdgeCollision & AxisAlignedRectangleCollider::TopEdge) == AxisAlignedRectangleCollider::TopEdge)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool Player::ValidateSpikesCollision(Spikes* spikes, unsigned char playerEdgeCollision, unsigned char spikesEdgeCollision)
	{
		float previousPlayerBottomEdge = m_PreviousPosition.y - PLAYER_HALF_HEIGHT;
		float playerBottomEdge = GetPosition().y - PLAYER_HALF_HEIGHT;
		float spikesTopEdge = spikes->GetPosition().y + SPIKES_HEIGHT * 0.5f;

		if ((previousPlayerBottomEdge > spikesTopEdge && playerBottomEdge < spikesTopEdge)
			|| previousPlayerBottomEdge == spikesTopEdge)
		{
			if ((playerEdgeCollision & AxisAlignedRectangleCollider::BottomEdge) == AxisAlignedRectangleCollider::BottomEdge
				&& (spikesEdgeCollision & AxisAlignedRectangleCollider::TopEdge) == AxisAlignedRectangleCollider::TopEdge)
			{
				return true;
			}
		}

		return false;
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
			m_CanDoubleJump = true;
		}
		else if ((playerEdgeCollision & AxisAlignedRectangleCollider::TopEdge) != 0)
		{
			//Its an ItemBox, and it has an action feature
			if (tile->GetType() == Tile::Item)
			{
				tile->Action();
			}
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
			if (m_MilletAmt >= MILLET_REQUIRED && IsKeyDown(Keyboard::Up))
			{
				m_ActiveRoom = LEVEL1_ROOM_NUM - 1;
				m_Level->SetActiveRoom(m_ActiveRoom);
				SetMusic(m_ActiveRoom);
			}
			else if (m_ActiveRoom != LEVEL1_ROOM_NUM - 2 && IsKeyDown(Keyboard::Up))
			{
				m_ActiveRoom++;
				m_Level->SetActiveRoom(m_ActiveRoom);
				SetMusic(m_ActiveRoom);
				
			}
			else if (m_Level->GetActiveRoomNum() != 0 && IsKeyDown(Keyboard::Down))
			{
				m_ActiveRoom--;
				m_Level->SetActiveRoom(m_ActiveRoom);
				SetMusic(m_ActiveRoom);
			}
			else if (m_ActiveRoom == LEVEL1_ROOM_NUM - 2 && IsKeyDown(Keyboard::Up))
			{
				m_Dialogue->SetText("You still need " + std::to_string(MILLET_REQUIRED - m_MilletAmt) + " millet to pass!");
				m_IsSpeaking = true;
			}
		}

		return resolveCollision;
	}
	bool Player::HandlePlatformCollision(Platform* platform, unsigned char playerEdgeCollision, unsigned char platformEdgeCollision)
	{
		bool resolveCollision = false;

		//Don't handle collision if the edge is unknown
		if (playerEdgeCollision == AxisAlignedRectangleCollider::UnknownEdge)
		{
			return resolveCollision;
		}

		//Local variables
		float previousPlayerBottomEdge = m_PreviousPosition.y - PLAYER_HALF_HEIGHT;
		float playerBottomEdge = GetPosition().y - PLAYER_HALF_HEIGHT;
		float platformTopEdge = platform->GetPosition().y + PLATFORM_SEGMENT_HEIGHT * 0.5f;

		if (GetLinearVelocity().y <= 0.0f && IsKeyDown(Keyboard::Down) == false)
		{
			if (Math::IsClose(playerBottomEdge, platformTopEdge, 2.5f)
				|| (previousPlayerBottomEdge > platformTopEdge && playerBottomEdge < platformTopEdge)
				|| previousPlayerBottomEdge == platformTopEdge)
			{
				if ((playerEdgeCollision & AxisAlignedRectangleCollider::BottomEdge) == AxisAlignedRectangleCollider::BottomEdge
					&& (platformEdgeCollision & AxisAlignedRectangleCollider::TopEdge) == AxisAlignedRectangleCollider::TopEdge)
				{
					m_IsInAir = false;
					m_CanDoubleJump = true;
					resolveCollision = true;
				}
			}
		}

		return resolveCollision;
	}
	void Player::HandleSpikesCollision(Spikes* spikes)
	{
		SetState(Dead);
	}

	void Player::HandleEnemyCollision(Enemy* enemy, unsigned char playerEdgeCollision)
	{
		if (enemy->GetType() == Enemy::EyeFly || enemy->GetType() == Enemy::SexyFish)
		{
			if ((playerEdgeCollision & AxisAlignedRectangleCollider::BottomEdge) != 0)
			{
				//The player landed on top of the enemy, set the enemy state to in-active
				//it will appear as if the enemy is dead
				enemy->SetIsActive(false);

				//Bounce the Player off the enemy's head
				m_LinearVelocity.y = PLAYER_JUMP_SPEED * 0.5f;
				m_IsInAir = true;
				m_Bonk->Stop();
				m_Bonk->Play();
			}
			else
			{
				//The Player collided with the enemy from the sides 
				//or top and has met their demise
				SetState(Dead);
			}
		}
		else if (enemy->GetType() == Enemy::NPCnormal)
		{
			if (m_IsSpeaking == false)
			{
				if (IsKeyDown(Keyboard::C))
				{
					if (m_IsJokeOn == true)
					{
						m_SpeakingJ->Stop();
						m_SpeakingJ->Play();
					}
					else
					{
						m_Speaking->Stop();
						m_Speaking->Play();
					}

					m_Dialogue->SetText(NPCNORMAL_SPEECH[Math::RandomInt(0, NPCNORMAL_SPEECH_NUM - 1)]);
					m_IsSpeaking = true;
				}
			}
		}
		else if (enemy->GetType() == Enemy::NPCgreta)
		{
			if (m_IsSpeaking == false)
			{
				if (IsKeyDown(Keyboard::C))
				{
					if (m_IsJokeOn == true)
					{
						m_SpeakingJ->Stop();
						m_SpeakingJ->Play();
					}
					else
					{
						m_Speaking->Stop();
						m_Speaking->Play();
					}

					if (m_EggAmt == 0 && m_FoundEgg == false)
					{
						m_Dialogue->SetText(NPCGRETA_SPEECH[0]);
						m_IsSpeaking = true;
					}
					else if (m_EggAmt != 0 && m_FoundEgg == false)
					{
						m_Dialogue->SetText(NPCGRETA_SPEECH[1]);
						m_IsSpeaking = true;
						m_FoundEgg = true;
						m_EggAmt--;
						m_MilletAmt++;
					}
					else if (m_EggAmt != 0 && m_FoundEgg == true)
					{
						m_Dialogue->SetText(NPCGRETA_SPEECH[2]);
						m_IsSpeaking = true;
						m_MilletAmt++;
					}
				}
			}
		}
		else if (enemy->GetType() == Enemy::NPCend)
		{
			if (m_IsSpeaking == false)
			{
				if (IsKeyDown(Keyboard::C))
				{
					if (m_IsJokeOn == true)
					{
						m_SpeakingJ->Stop();
						m_SpeakingJ->Play();
					}
					else
					{
						m_Speaking->Stop();
						m_Speaking->Play();
					}

					m_Dialogue->SetText(NPCEND_SPEECH[Math::RandomInt(0, NPCEND_SPEECH_NUM - 1)]);
					m_IsSpeaking = true;
				}
			}
		}
	}
	void Player::HandlePickupCollision(Pickup* pickup)
	{
		if (pickup->GetType() == Pickup::Seed)
		{
			m_SeedAmt++;
			m_ItemGet->Stop();
			m_ItemGet->Play();
		}
		else if (pickup->GetType() == Pickup::Millet)
		{
			m_MilletAmt++;
			m_ItemGet->Stop();
			m_ItemGet->Play();
		}
		else if (pickup->GetType() == Pickup::Egg)
		{
			m_EggAmt++;
			m_ItemGet->Stop();
			m_ItemGet->Play();
		}
		else if (pickup->GetType() == Pickup::Wings)
		{
			for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
			{
				m_Music[i]->Stop();
			}

			if (m_MilletAmt >= MILLET_REQUIRED)
			{
				m_WinMusic->Play();
				m_Inventory->SetText("You finished with " + std::to_string(m_SeedAmt) + "/" + std::to_string(TOTAL_SEED_NUM) + " seeds!");
			}

			m_GotWings = true;
		}

		pickup->Consume();
	}
}