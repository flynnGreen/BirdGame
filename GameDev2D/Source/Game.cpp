#include "Game.h"
#include "Constants.h"

namespace GameDev2D
{
	Game::Game() :
		m_Level(nullptr),
		m_SpriteBatch(nullptr),
		m_LoadStep((int)LoadStep_Initialize)
	{
	}

	Game::~Game()
	{
		SafeDelete(m_Level);
		SafeDelete(m_SpriteBatch);

		UnloadTexture("Assets");
	}

	void Game::Update(double delta)
	{
		//Ensure this if statement is always the first statement in this method
		if (IsLoading() == true)
		{
			LoadStep();
			return;
		}

		m_Level->Update(delta);
	}

	void Game::Draw()
	{
		//Ensure this if statement is always the first statement in this method
		if (IsLoading() == true)
		{
			//Local variables
			Graphics* g = Services::GetGraphics();
			Vector2 screenSize(GetScreenWidth(), GetScreenHeight());
			Color bgColor = Color::CornflowerBlueColor();
			Color barColor = Color::ForestGreenColor();
			float pctLoaded = (float)m_LoadStep / (float)LoadStep_Complete;

			//Draw the Background - cornflower blue rectangle
			g->DrawRectangle(Vector2::Zero, screenSize, Rotation::Zero, Vector2::Zero, bgColor, true);

			//Draw the load bar outline
			Vector2 outerBarSize(screenSize.x * 0.4f, screenSize.y * 0.05f);
			Vector2 outerBarPosition = (screenSize - outerBarSize) * 0.5f;
			g->DrawRectangle(outerBarPosition, outerBarSize, Rotation::Zero, Vector2::Zero, barColor, false);

			//Draw the load bar outline
			Vector2 innerBarMaxSize(outerBarSize.x - 4.0f, outerBarSize.y - 4.0f);
			Vector2 innerBarAcutalSize(innerBarMaxSize.x * pctLoaded, innerBarMaxSize.y);
			Vector2 innerBarPosition = (screenSize - innerBarMaxSize) * 0.5f;
			g->DrawRectangle(innerBarPosition, innerBarAcutalSize, Rotation::Zero, Vector2::Zero, barColor, true);

			return;
		}

		m_SpriteBatch->Begin();

		m_Level->Draw(m_SpriteBatch);

		m_SpriteBatch->End();

		m_Level->DrawHUD();

		m_Level->DrawFader();
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
		if (IsLoading() == false)
		{
			//Only handle input when the loading is done
		}
	}

	void Game::HandleRightMouseClick(float mouseX, float mouseY)
	{
		if (IsLoading() == false)
		{
			//Only handle input when the loading is done
		}
	}

	void Game::HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY)
	{
		if (IsLoading() == false)
		{
			//Only handle input when the loading is done
		}
	}

	void Game::HandleKeyPress(Keyboard::Key key)
	{
		if (IsLoading() == false)
		{
			m_Level->HandleKeyPress(key);
		}
	}

	void Game::HandleKeyReleased(Keyboard::Key key)
	{
		if (IsLoading() == false)
		{
			m_Level->HandleKeyReleased(key);
		}
	}

	void Game::LoadStep()
	{
		switch (m_LoadStep)
		{
		case LoadStep_Initialize:
		{
			m_SpriteBatch = new SpriteBatch();
		}
		break;

		case LoadStep_Textures:
		{
			LoadTexture("Assets");
			LoadFont("Hanged Letters_32");
			LoadFont("OpenSans-CondBold_22");
		}
		break;

		case LoadStep_Audio:
		{
			LoadAudio("Death");
			LoadAudio("Jump");
			LoadAudio("JumpReal");
			LoadAudio("JumpReal2");
			LoadAudio("DeathReal");
			LoadAudio("JokeModeActivated");
			LoadAudio("Birdsong");
			LoadAudio("Room1Music");
			LoadAudio("Room2Music");
			LoadAudio("Room3Music");
			LoadAudio("Bonk");
			LoadAudio("ItemGet");
			LoadAudio("WinMusic");
			LoadAudio("Speaking");
			LoadAudio("JokeSpeaking");
		}
		break;

		case LoadStep_Level:
		{
			m_Level = new Level();
		}
		break;

		case LoadStep_Room1:
		{
			m_Level->LoadRoom(0);
		}
		break;

		case LoadStep_Room2:
		{
			m_Level->LoadRoom(1);
		}
		break;

		case LoadStep_Room3:
		{
			m_Level->LoadRoom(2);
		}
		break;

		case LoadStep_Player:
		{
			m_Level->LoadPlayer();
		}
		break;

		default:
			break;
		}

		//After the load step, increment the m_LoadStep variable
		m_LoadStep++;
	}

	bool Game::IsLoading()
	{
		return m_LoadStep != (int)LoadStep_Complete;
	}
}