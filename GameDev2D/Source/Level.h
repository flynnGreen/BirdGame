#pragma once

#include <GameDev2D.h>
#include "Room.h"


namespace GameDev2D
{
	class Level
	{
	public:
		Level();
		~Level();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch);
		void Reset();

		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);

	protected:
		Room* m_Room;
	};
}