#pragma once

#include <GameDev2D.h>
#include "Tile.h"
#include "Platform.h"
#include "Spikes.h"
#include "SexyFish.h"

namespace GameDev2D
{
	class Level;

	class Room
	{
	public:
		Room(Level* level, const std::string& filename);
		~Room();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch);
		void Reset();

		unsigned char GetRows();
		unsigned char GetColumns();

		void SetIsActive(bool isActive);
		bool IsOnScreen(Tile* tile);

		float GetWidth();
		float GetHeight();

		Level* GetLevel();

		Tile* GetTile(unsigned char row, unsigned char column);
		bool Validate(unsigned char row, unsigned char column);

		//GameObject methods
		GameObject* AddGameObject(GameObject* gameObject);
		unsigned int GetNumberOfGameObjects();
		GameObject* GetGameObjectAtIndex(int index);
		void RemoveGameObjectAtIndex(int index);
		void RemoveAllGameObjects();

	private:
		//Loads the raw data and creates Tile objects
		void Load(const std::string& filename);

		//Method that takes in the tile data and the row and column used to create
		//a single Tile object and returns a pointer to the newly created Tile
		Tile* CreateNewTile(unsigned char data, unsigned char row, unsigned char col);

		//Member variables
		Level* m_Level;
		Tile*** m_Tiles;  //Used as a dynamic 2D-Array of Tile pointers
		unsigned char m_NumRows;
		unsigned char m_NumColumns;
		std::vector<GameObject*> m_GameObjects;
		SpriteAtlas* m_Background;
		int m_ActiveRoom;
		SexyFish* m_Sexy;
	};
}