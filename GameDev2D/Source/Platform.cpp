#include "Platform.h"
#include "Room.h"
#include "Level.h"
#include "Player.h"


namespace GameDev2D
{
	Platform::Platform(Room* room, Vector2 startPosition, Vector2 displacement, double duration) :
		GameObject(),
		m_Room(room),
		m_Segments{},
		m_Collider(nullptr),
		m_StartPosition(startPosition),
		m_Displacement(displacement),
		m_Timer(duration)
	{
		//Calculate the starting position of the segments
		float posX = -GetWidth() * 0.5f;

		//Loop through and create each SpriteAtlas, 
		//and determine it's frame and position
		for (int i = 0; i < PLATFORM_NUM_SEGMENTS; i++)
		{
			//Create the SpriteAtlas object
			m_Segments[i] = new SpriteAtlas("Assets");

			//Calculate the correct frame to use
			bool isFirst = i == 0;
			bool isLast = i == PLATFORM_NUM_SEGMENTS - 1;
			std::string frame = isFirst ? "Platform-L" : (isLast ? "Platform-R" : "Platform-M");
			m_Segments[i]->UseFrame(frame);

			//Set the anchor, position and attach the SpriteAtlas to the Platform 
			m_Segments[i]->SetAnchor(0.0f, 0.5f);
			m_Segments[i]->SetPosition(posX, 0.0f);
			m_Segments[i]->AttachTo(this);

			//Increment the position
			posX += TILE_SIZE;
		}

		//Add the collider
		CollisionFilter filter = CollisionFilter(PLATFORM_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		m_Collider = AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Static, filter);

		//Set the position
		SetPosition(m_StartPosition);

		//Set the timer to loop and start it
		m_Timer.SetDoesLoop(true);
		m_Timer.Start();
	}

	Platform::~Platform()
	{
		for (int i = 0; i < PLATFORM_NUM_SEGMENTS; i++)
		{
			SafeDelete(m_Segments[i]);
		}
	}

	void Platform::Update(double delta)
	{
		//Update the Timer
		m_Timer.Update(delta);

		//Calculate the displacement, using a sine wave
		float pct = m_Timer.GetPercentageElapsed();
		float radians = (2.0f * M_PI) * pct;
		Vector2 displacement = m_Displacement * sinf(radians);

		//Calculate the position
		Vector2 position = m_StartPosition + displacement;

		//Calculate the difference in position
		Vector2 difference = position - GetPosition();

		//Set the position
		SetPosition(position);

		//Get the Player pointer
		Player* player = m_Room->GetLevel()->GetPlayer();

		//Check if the Player is colliding with the Platform
		if (player->GetCollider()->IsColliding(GetCollider()) == true)
		{
			//Get the collider edge flags for the Player and the Platform
			unsigned char playerEdgeCollision = player->GetCollider()->GetEdgeCollision();
			unsigned char platformEdgeCollision = GetCollider()->GetEdgeCollision();

			if (player->ValidatePlatformCollision(this, playerEdgeCollision, platformEdgeCollision) == true)
			{
				player->Translate(difference);
			}
		}
	}

	void Platform::Draw(SpriteBatch* spriteBatch)
	{
		for (int i = 0; i < PLATFORM_NUM_SEGMENTS; i++)
		{
			spriteBatch->Draw(m_Segments[i]);
		}
	}

	void Platform::Reset()
	{
	}

	float Platform::GetWidth()
	{
		return PLATFORM_SEGMENT_WIDTH * (float)PLATFORM_NUM_SEGMENTS;
	}

	float Platform::GetHeight()
	{
		return PLATFORM_SEGMENT_HEIGHT;
	}

	AxisAlignedRectangleCollider* Platform::GetCollider()
	{
		return m_Collider;
	}
}