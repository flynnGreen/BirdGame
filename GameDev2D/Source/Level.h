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
		void DrawFader();
		void Reset();

		Room* GetActiveRoom();
		int GetActiveRoomNum();
		Player* GetPlayer();

		void SetActiveRoom(unsigned int index);

		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);

		Room* LoadRoom(int roomNum);
		Player* LoadPlayer();

		enum State
		{
			Gameplay = 0,
			Respawning,
			RoomChange
		};

		State GetState();

		enum Fader
		{
			No_Fade = 0,
			Fade_In,
			Fade_Out
		};

		bool IsFading();

	protected:
		void Respawn();
		void TransitionToRoom(unsigned int index);

		Room* m_Room[LEVEL1_ROOM_NUM];
		Player* m_Player;

	private:
		Polygon* m_BlackOverlay;
		State m_State;
		Fader m_Fader;
		Timer m_FadeTimer;
		unsigned int m_CurrentRoom = 0;
		unsigned int m_NextRoom = 0;
	};
}