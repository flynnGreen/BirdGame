#pragma once

#include "Tile.h"
#include "Timer.h"

namespace GameDev2D
{
	class Room;
	class Pickup;

	class Item : public Tile
	{
	public:
		Item(Room* room, unsigned char row, unsigned char col, bool hasCollider);
		~Item();

		Tile::Type GetType() override;
		void Draw(SpriteBatch* spriteBatch = nullptr) override;
		void Update(double delta) override;

		void Reset() override;
		void Action() override;

		void SetPickup(Pickup* pickup);
		Pickup* GetPickup();

	private:
		SpriteAtlas* m_Tile;

		enum State
		{
			Enabled = 0,
			Animating,
			Disabled
		};

		State m_State;
		Timer m_ScaleTimer;
		Room* m_Room;
		Pickup* m_Pickup;
	};
}