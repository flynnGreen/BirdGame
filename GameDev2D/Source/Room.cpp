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

		bool isActive = filename == LEVEL1_NAMES[0];
		SetIsActive(isActive);
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
				if (IsOnScreen(m_Tiles[r][c]) == true)
				{
					m_Tiles[r][c]->SetIsActive(true);
					m_Tiles[r][c]->Update(delta);
				}
				else
				{
					m_Tiles[r][c]->SetIsActive(false);
				}
			}
		}
	}

	void Room::Draw(SpriteBatch* spriteBatch)
	{
		for (unsigned char r = 0; r < m_NumRows; r++)
		{
			for (unsigned char c = 0; c < m_NumColumns; c++)
			{
				if (m_Tiles[r][c]->GetType() != Tile::Empty
					&& m_Tiles[r][c]->IsActive() == true)
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

	void Room::SetIsActive(bool isActive)
	{
		for (unsigned char r = 0; r < GetRows(); r++)
		{
			for (unsigned char c = 0; c < GetColumns(); c++)
			{
				Tile* tile = m_Tiles[r][c];
				bool activeState = isActive;

				if (isActive == true)
				{
					activeState = IsOnScreen(tile);
				}
				else
				{
					activeState = false;
				}

				tile->SetIsActive(activeState);
			}
		}
	}

	bool Room::IsOnScreen(Tile* tile)
	{
		Vector2 cameraPosition = GetCamera()->GetPosition();
		float left = cameraPosition.x - GetHalfScreenWidth() - HALF_TILE_SIZE;
		float right = cameraPosition.x + GetHalfScreenWidth() + HALF_TILE_SIZE;
		float top = cameraPosition.y + GetHalfScreenHeight() + HALF_TILE_SIZE;
		float bottom = cameraPosition.y - GetHalfScreenHeight() - HALF_TILE_SIZE;

		Vector2 tilePosition = tile->GetPosition();
		return tilePosition.x >= left
			&& tilePosition.x <= right
			&& tilePosition.y >= bottom
			&& tilePosition.y <= top;
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
		bool hasVariant = (data & 2) != 0;

		if ((data & Tile::Main) == Tile::Main)
		{
			return new MainTile(row, col, hasCollider, hasVariant);
		}
		if ((data & Tile::Water) == Tile::Water)
		{
			return new Water(row, col, hasCollider, hasVariant);
		}
		if ((data & Tile::Item) == Tile::Item)
		{
			return new Item(row, col, hasCollider);
		}
		if ((data & Tile::Tree) == Tile::Tree)
		{
			return new Tree(row, col, hasCollider, hasVariant);
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