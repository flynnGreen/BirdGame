#pragma once

#include <GameDev2D.h>
#include "Room.h"
#include "Constants.h"
#include "Player.h"


namespace GameDev2D
{
	class Level
	{
	public:
		Level();
		~Level();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch);
		void DrawHUD();
		void Reset();

		Room* GetActiveRoom();
		int GetActiveRoomNum();
		Player* GetPlayer();

		void SetActiveRoom(unsigned int index);

		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);

	protected:
		Room* m_Room[LEVEL1_ROOM_NUM];
		Player* m_Player;

	private:
		unsigned int m_CurrentRoom = 0;
	};
}