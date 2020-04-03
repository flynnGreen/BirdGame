#include "Level.h"
#include "Constants.h"

namespace GameDev2D
{
	Level::Level() :
		m_Player(nullptr)
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i] = new Room(LEVEL1_NAMES[i]);
		}

		m_Player = new Player(this);
	}

	Level::~Level()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			SafeDelete(m_Room[i]);
		}
		SafeDelete(m_Player);
	}

	void Level::Update(double delta)
	{

		Vector2 cameraPosition = GetCamera()->GetPosition();

		if (m_Player->IsDead() == false)
		{
			Vector2 playerPosition = m_Player->GetPosition();
			Vector2 deltaPosition = cameraPosition - playerPosition;

			if (fabsf(deltaPosition.x) > 1.0f)
			{
				cameraPosition.x -= deltaPosition.x;
			}

			if (fabsf(deltaPosition.y) > 1.0f)
			{
				cameraPosition.y -= deltaPosition.y;
			}
		}

		cameraPosition.x = Math::Clamp(cameraPosition.x, GetHalfScreenWidth(), m_Room[m_CurrentRoom]->GetWidth() - GetHalfScreenWidth());
		cameraPosition.y = Math::Clamp(cameraPosition.y, GetHalfScreenHeight(), m_Room[m_CurrentRoom]->GetHeight() - GetHalfScreenHeight());

		GetCamera()->SetPosition(cameraPosition);

		/*if (IsKeyDown(Keyboard::Up))
		{
			GetCamera()->SetPositionY(GetCamera()->GetPosition().y + CAMERA_SPEED);
		}
		if (IsKeyDown(Keyboard::Down))
		{
			GetCamera()->SetPositionY(GetCamera()->GetPosition().y - CAMERA_SPEED);
		}
		if (IsKeyDown(Keyboard::Right))
		{
			GetCamera()->SetPositionX(GetCamera()->GetPosition().x + CAMERA_SPEED);
		}
		if (IsKeyDown(Keyboard::Left))
		{
			GetCamera()->SetPositionX(GetCamera()->GetPosition().x - CAMERA_SPEED);
		}*/

		m_Room[m_CurrentRoom]->Update(delta);

		if (m_Player != nullptr)
		{
			m_Player->Update(delta);
		}
	}

	void Level::Draw(SpriteBatch* spriteBatch)
	{
		m_Room[m_CurrentRoom]->Draw(spriteBatch);

		if (m_Player != nullptr)
		{
			m_Player->Draw(spriteBatch);
		}
	}

	void Level::Reset()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i]->Reset();
		}
		if (m_Player != nullptr)
		{
			m_Player->Reset();
		}
	}

	Room* Level::GetActiveRoom()
	{
		return m_Room[m_CurrentRoom];
	}

	int Level::GetActiveRoomNum()
	{
		return m_CurrentRoom;
	}

	void Level::SetActiveRoom(unsigned int index)
	{
		if (m_CurrentRoom != index && index < LEVEL1_ROOM_NUM)
		{
			//Deactivate the current active room
			GetActiveRoom()->SetIsActive(false);

			//Set the new active room index
			m_CurrentRoom = index;

			//Activate the current active room
			GetActiveRoom()->SetIsActive(true);

			//Reset the camera's position
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
		}
	}

	void Level::HandleKeyPress(Keyboard::Key key)
	{
		if (key == Keyboard::R)
		{
			Reset();
		}

		if (key == Keyboard::One)
		{
			SetActiveRoom(0);
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
			m_Player->Reset();
		}
		if (key == Keyboard::Two)
		{
			SetActiveRoom(1);
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
			m_Player->Reset();
		}
		if (key == Keyboard::Three)
		{
			SetActiveRoom(2);
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
			m_Player->Reset();
		}
		else
		{
			if (m_Player != nullptr)
			{
				m_Player->HandleKeyPress(key);
			}
		}
	}

	void Level::HandleKeyReleased(Keyboard::Key key)
	{
		if (m_Player != nullptr)
		{
			m_Player->HandleKeyReleased(key);
		}
	}
}

