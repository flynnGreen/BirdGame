#pragma once

#include <GameDev2D.h>
#include "Tile.h"

namespace GameDev2D
{
	class Room
	{
	public:
		Room(const std::string& filename);
		~Room();

		void Update(double delta);
		void Draw(SpriteBatch* spriteBatch);
		void Reset();

		unsigned char GetRows();
		unsigned char GetColumns();

		float GetWidth();
		float GetHeight();

	private:
		//Loads the raw data and creates Tile objects
		void Load(const std::string& filename);

		//Method that takes in the tile data and the row and column used to create
		//a single Tile object and returns a pointer to the newly created Tile
		Tile* CreateNewTile(unsigned char data, unsigned char row, unsigned char col);

		//Member variables
		Tile*** m_Tiles;  //Used as a dynamic 2D-Array of Tile pointers
		unsigned char m_NumRows;
		unsigned char m_NumColumns;
	};
}