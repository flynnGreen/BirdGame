#include "Room.h"
#include "Level.h"
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
	Room::Room(Level* level, const std::string& filename) :
		m_Tiles(nullptr),
		m_NumRows(0),
		m_NumColumns(0),
		m_Level(level)
	{
		//Load the Room
		Load(filename);

		bool isActive = filename == LEVEL1_NAMES[0];
		SetIsActive(isActive);

		//Create the Platforms and music
		for (int i = 0; i < LEVEL1_ROOM_NUM; i++)
		{
			if (filename == LEVEL1_NAMES[i])
			{
				Platform* platform = new Platform(this,
					PLATFORM_START_POSITION[i],
					PLATFORM_DISPLACEMENT[i],
					PLATFORM_DURATION[i]);

				//Add the Platform to the Room
				this->AddGameObject(platform);
			}
		}

		//Create still platforms
		if (filename == LEVEL1_NAMES[0])
		{
			Platform* stillPlatform1 = new Platform(this, STILL_PLATFORM_START_POSITION[0], Vector2::Zero, 0);

			//Add the Platform to the Room
			this->AddGameObject(stillPlatform1);

			Platform* stillPlatform2 = new Platform(this, STILL_PLATFORM_START_POSITION[1], Vector2::Zero, 0);

			//Add the Platform to the Room
			this->AddGameObject(stillPlatform2);
		}
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
		RemoveAllGameObjects();
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
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Update(delta);
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
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Draw(spriteBatch);
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

		GetCamera()->SetPosition(GetHalfScreenWidth(), GetHalfScreenHeight());

		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->Reset();
		}
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
		for (int i = 0; i < m_GameObjects.size(); i++)
		{
			m_GameObjects.at(i)->SetIsActive(isActive);
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

	Level* Room::GetLevel()
	{
		return m_Level;
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

	GameObject* Room::AddGameObject(GameObject* gameObject)
	{
		if (gameObject != nullptr)
		{
			m_GameObjects.push_back(gameObject);
		}
		return gameObject;
	}

	unsigned int Room::GetNumberOfGameObjects()
	{
		return m_GameObjects.size();
	}

	GameObject* Room::GetGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			return m_GameObjects.at(index);
		}
		return nullptr;
	}

	void Room::RemoveGameObjectAtIndex(int index)
	{
		if (index >= 0 && index < GetNumberOfGameObjects())
		{
			SafeDelete(m_GameObjects.at(index));
			m_GameObjects.erase(m_GameObjects.begin() + index);
		}
	}

	void Room::RemoveAllGameObjects()
	{
		for (int i = 0; i < GetNumberOfGameObjects(); i++)
		{
			SafeDelete(m_GameObjects.at(i));
		}
		m_GameObjects.clear();
	}
}