#include "Level.h"
#include "Constants.h"

namespace GameDev2D
{
	Level::Level()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i] = new Room(LEVEL1_NAMES[i]);
		}
	}

	Level::~Level()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			SafeDelete(m_Room[i]);
		}
	}

	void Level::Update(double delta)
	{

		Vector2 cameraPosition = GetCamera()->GetPosition();

		cameraPosition.x = Math::Clamp(cameraPosition.x, GetHalfScreenWidth(), m_Room[m_CurrentRoom]->GetWidth() - GetHalfScreenWidth());
		cameraPosition.y = Math::Clamp(cameraPosition.y, GetHalfScreenHeight(), m_Room[m_CurrentRoom]->GetHeight() - GetHalfScreenHeight());

		GetCamera()->SetPosition(cameraPosition);

		if (IsKeyDown(Keyboard::Up))
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
		}

		m_Room[m_CurrentRoom]->Update(delta);
	}

	void Level::Draw(SpriteBatch* spriteBatch)
	{
		m_Room[m_CurrentRoom]->Draw(spriteBatch);
	}

	void Level::Reset()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i]->Reset();
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
			m_CurrentRoom = 0;
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
		}
		if (key == Keyboard::Two)
		{
			m_CurrentRoom = 1;
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
		}
		if (key == Keyboard::Three)
		{
			m_CurrentRoom = 2;
			GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());
		}
	}

	void Level::HandleKeyReleased(Keyboard::Key key)
	{

	}
}