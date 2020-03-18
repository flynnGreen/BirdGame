#include "Level.h"
#include "Constants.h"

namespace GameDev2D
{
	Level::Level()
	{
		m_Room = new Room("Level1_Room1");
	}

	Level::~Level()
	{
		SafeDelete(m_Room);
	}

	void Level::Update(double delta)
	{
		//TODO: Move the Camera here

		m_Room->Update(delta);
	}

	void Level::Draw(SpriteBatch* spriteBatch)
	{
		m_Room->Draw(spriteBatch);
	}

	void Level::Reset()
	{
		m_Room->Reset();
	}

	void Level::HandleKeyPress(Keyboard::Key key)
	{
		if (key == Keyboard::R)
		{
			Reset();
		}
	}

	void Level::HandleKeyReleased(Keyboard::Key key)
	{

	}
}