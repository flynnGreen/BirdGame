#include "Level.h"
#include "Constants.h"

namespace GameDev2D
{
	Level::Level() :
		m_Player(nullptr),
		m_BlackOverlay(nullptr),
		m_State(Respawning),
		m_Fader(Fade_Out),
		m_FadeTimer(FADE_DURATION)
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i] = new Room(this, LEVEL1_NAMES[i]);
		}

		m_Player = new Player(this);

		//Create a Polygon object used for Room transitions
		m_BlackOverlay = new Polygon();
		m_BlackOverlay->MakeRectangle(GetScreenWidth(), GetScreenHeight(), true);
		m_BlackOverlay->SetColor(Color::BlackColor(1.0f));
		m_BlackOverlay->SetAnchor(0.5f, 0.5f);

		//Start the Fade timer
		m_FadeTimer.Start();
	}

	Level::~Level()
	{
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			SafeDelete(m_Room[i]);
		}
		SafeDelete(m_Player);
		SafeDelete(m_BlackOverlay);
	}

	void Level::Update(double delta)
	{
		m_Room[m_CurrentRoom]->Update(delta);

		if (m_State == Gameplay)
		{
			if (m_Player != nullptr)
			{
				m_Player->Update(delta);
			}

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
			else
			{
				Respawn();
			}

			cameraPosition.x = Math::Clamp(cameraPosition.x, GetHalfScreenWidth(), m_Room[m_CurrentRoom]->GetWidth() - GetHalfScreenWidth());
			cameraPosition.y = Math::Clamp(cameraPosition.y, GetHalfScreenHeight(), m_Room[m_CurrentRoom]->GetHeight() - GetHalfScreenHeight());

			GetCamera()->SetPosition(cameraPosition);
		}

		//Is there a fade in or fade out happening
		if (IsFading() == true)
		{
			//Update the Fade Timer
			m_FadeTimer.Update(delta);

			if (m_Fader == Fade_In)
			{
				m_BlackOverlay->SetAlpha(m_FadeTimer.GetPercentageElapsed());

				//Is the Timer done?
				if (m_FadeTimer.IsDone() == true)
				{
					//Change the state to Fade Out
					m_Fader = Fade_Out;

					//Restart the Timer for the Fade Out
					m_FadeTimer.Restart();

					if (m_State == Respawning)
					{
						GetActiveRoom()->Reset();
						m_Player->Reset();
					}
					else if (m_State == RoomChange)
					{
						SetActiveRoom(m_NextRoom);
					}
				}
			}
			else if (m_Fader == Fade_Out)
			{
				//Set the Black overlay's alpha
				m_BlackOverlay->SetAlpha(m_FadeTimer.GetPercentageRemaining());

				//Is the Timer done? Set the State to Gameplay
				if (m_FadeTimer.IsDone() == true)
				{
					m_State = Gameplay;
					m_Fader = No_Fade;
				}
			}
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

	void Level::DrawHUD()
	{
		m_Player->DrawHUD();
	}

	void Level::DrawFader()
	{
		//Draw the Fade
		if (IsFading() == true)
		{
			Vector2 position = GetCamera()->GetPosition();
			m_BlackOverlay->SetPosition(position);
			m_BlackOverlay->Draw();
		}
	}

	void Level::Reset()
	{
		Respawn();

		//Deactivate all rooms
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			m_Room[i]->SetIsActive(false);
		}

		GetActiveRoom()->SetIsActive(true);
		GetActiveRoom()->Reset();

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

	Player* Level::GetPlayer()
	{
		return m_Player;
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

			//Reset the player
			m_Player->Reset();
		}
	}

	void Level::HandleKeyPress(Keyboard::Key key)
	{
		if (key == Keyboard::R)
		{
			Reset();
			m_Player->Reset();
		}

		if (key == Keyboard::One)
		{
			TransitionToRoom(0);
		}
		if (key == Keyboard::Two)
		{
			TransitionToRoom(1);
		}
		if (key == Keyboard::Three)
		{
			TransitionToRoom(2);
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

	Level::State Level::GetState()
	{
		return m_State;
	}

	bool Level::IsFading()
	{
		return m_FadeTimer.IsRunning();
	}

	void Level::Respawn()
	{
		m_State = Respawning;
		m_Fader = Fade_In;
		m_FadeTimer.Restart();
	}

	void Level::TransitionToRoom(unsigned int index)
	{
		if (m_State == Gameplay)
		{
			m_NextRoom = index;
			m_State = RoomChange;
			m_Fader = Fade_In;
			m_FadeTimer.Restart();
		}
	}
}

