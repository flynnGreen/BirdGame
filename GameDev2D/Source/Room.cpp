#include "Room.h"
#include "Constants.h"
#include "EmptyTile.h"
#include "MainTile.h"
#include "Water.h"
#include "Item.h"
#include "Tree.h"
#include "House.h"
#include "Teleport.h"
#include <fstream>


namespace GameDev2D
{
	Room::Room(const std::string& filename) :
		m_Tiles(nullptr),
		m_NumRows(0),
		m_NumColumns(0)
	{
		//Load the Room
		Load(filename);
	}

	Room::~Room()
	{
		if (m_Tiles != nullptr)
		{
			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				for (unsigned char c = 0; c < m_NumColumns; c++)
				{
					SafeDelete(m_Tiles[r][c]);
				}
				SafeDeleteArray(m_Tiles[r]);
			}
			SafeDeleteArray(m_Tiles);
		}
	}

	void Room::Update(double delta)
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				m_Tiles[r][c]->Update(delta);
			}
		}
	}

	void Room::Draw(SpriteBatch* spriteBatch)
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				if (m_Tiles[r][c]->GetType() != Tile::Empty)
				{
					m_Tiles[r][c]->Draw(spriteBatch);
				}
			}
		}
	}

	void Room::Reset()
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				m_Tiles[r][c]->Reset();
			}
		}

		GetCamera()->SetPosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
	}

	unsigned char Room::GetRows()
	{
		return m_NumRows;
	}

	unsigned char Room::GetColumns()
	{
		return m_NumColumns;
	}

	float Room::GetWidth()
	{
		return (float)GetColumns() * TILE_SIZE;
	}

	float Room::GetHeight()
	{
		return (float)GetRows() * TILE_SIZE;
	}

	void Room::Load(const std::string& filename)
	{
		unsigned char** tiles = nullptr;
		Application* app = Services::GetApplication();
		std::string path = app->GetPathForResourceInDirectory(filename.c_str(), "bin", "Data");
		std::ifstream input;
		input.open(path, std::ios::in | std::ios::binary);

		//Did the file open
		if (input.is_open() == true)
		{
			//Read how many rows and columns there are
			input.read((char*)& m_NumRows, sizeof(unsigned char));
			input.read((char*)& m_NumColumns, sizeof(unsigned char));

			//Allocate the temp tiles array
			tiles = new unsigned char* [m_NumRows];

			//Loop through and load all the columns
			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				//Allocate the columns array for r
				tiles[r] = new unsigned char[m_NumColumns];

				size_t bytes = sizeof(unsigned char) * m_NumColumns;
				input.read((char*)tiles[r], bytes);
			}

			//Close the ifstream
			input.close();
		}

		//Ensure that there are rows and columns
		if (m_NumRows > 0 && m_NumColumns > 0)
		{
			//Allocate the array of Tile* arrays
			m_Tiles = new Tile * *[m_NumRows];

			//Loop through and create the Tiles
			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				//Allocate the array of Tile*
				m_Tiles[r] = new Tile * [m_NumColumns];

				//Loop through and create each Tile object
				for (unsigned char c = 0; c < m_NumColumns; c++)
				{
					//The CreateNewTile method ensures the correct Tile object is created
					m_Tiles[r][c] = CreateNewTile(tiles[r][c], r, c);
				}
			}
		}

		//Delete the temporary tiles array
		if (tiles != nullptr)
		{
			for (unsigned char r = 0; r < m_NumRows; r++)
			{
				SafeDeleteArray(tiles[r]);
			}
			SafeDeleteArray(tiles);
		}
	}

	Tile* Room::CreateNewTile(unsigned char data, unsigned char row, unsigned char col)
	{
		bool hasCollider = (data & 1) != 0;

		if ((data & Tile::Main) == Tile::Main)
		{
			return new MainTile(row, col, hasCollider);
		}
		if ((data & Tile::Water) == Tile::Water)
		{
			return new Water(row, col, hasCollider);
		}
		if ((data & Tile::Item) == Tile::Item)
		{
			return new Item(row, col, hasCollider);
		}
		if ((data & Tile::Tree) == Tile::Tree)
		{
			return new Tree(row, col, hasCollider);
		}
		if ((data & Tile::House) == Tile::House)
		{
			return new House(row, col, hasCollider);
		}
		if ((data & Tile::Teleport) == Tile::Teleport)
		{
			return new Teleport(row, col, hasCollider);
		}
		return new EmptyTile(row, col);
	}

}