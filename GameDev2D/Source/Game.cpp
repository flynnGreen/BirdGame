#include "Game.h"


namespace GameDev2D
{
	Game::Game() :
		m_Level(nullptr),
		m_SpriteBatch(nullptr)
	{
		LoadTexture("Assets");

		m_Level = new Level();
		m_SpriteBatch = new SpriteBatch();
	}

	Game::~Game()
	{
		SafeDelete(m_Level);
		SafeDelete(m_SpriteBatch);

		UnloadTexture("Assets");
	}

	void Game::Update(double delta)
	{
		m_Level->Update(delta);
	}

	void Game::Draw()
	{
		m_SpriteBatch->Begin();

		m_Level->Draw(m_SpriteBatch);

		m_SpriteBatch->End();

		m_Level->DrawHUD();
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
	
	}

	void Game::HandleRightMouseClick(float mouseX, float mouseY)
	{

	}

	void Game::HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY)
	{
		
	}

	void Game::HandleKeyPress(Keyboard::Key key)
	{
		m_Level->HandleKeyPress(key);
	}

	void Game::HandleKeyReleased(Keyboard::Key key)
	{
		m_Level->HandleKeyReleased(key);
	}
}