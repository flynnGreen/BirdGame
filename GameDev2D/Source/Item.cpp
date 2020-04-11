#include "Item.h"
#include "Constants.h"
#include "Room.h"
#include "SeedPickup.h"

namespace GameDev2D
{
	Item::Item(Room* room, unsigned char row, unsigned char col, bool hasCollider) :
		Tile(row, col, hasCollider),
		m_Tile(nullptr),
		m_State(Enabled),
		m_ScaleTimer(ITEM_BOX_SCALE_TIMER),
		m_Room(room),
		m_Pickup(nullptr)
	{
		m_Tile = new SpriteAtlas("Assets");
		m_Tile->UseFrame("Item");
		m_Tile->SetAnchor(0.5f, 0.5f);
		m_Tile->AttachTo(this);
	}

	Item::~Item()
	{
		SafeDelete(m_Tile);
		SafeDelete(m_Pickup);
	}

	Tile::Type Item::GetType()
	{
		return Tile::Item;
	}

	void Item::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Tile);

		if (m_Pickup != nullptr)
		{
			m_Pickup->Draw(spriteBatch);
		}
	}

	void Item::Update(double delta)
	{
		if (m_State == Animating)
		{
			if (m_ScaleTimer.IsRunning() == true)
			{
				m_ScaleTimer.Update(delta);

				float radians = M_PI * m_ScaleTimer.GetPercentageElapsed();
				float scale = 1.0f + 0.1f * sinf(radians);
				m_Tile->SetScale(Vector2(scale, scale));

				if (m_ScaleTimer.IsDone() == true)
				{
					m_State = Disabled;
					m_Tile->UseFrame("Item Empty");
				}
			}
		}
		if (m_Pickup != nullptr)
		{
			m_Pickup->Update(delta);
		}
	}

	void Item::Reset()
	{
		m_State = Enabled;
		m_Tile->UseFrame("Item");
	}

	void Item::Action()
	{
		if (m_State == Enabled)
		{
			m_ScaleTimer.Restart();
			m_State = Animating;
		}
		if (m_Pickup != nullptr)
		{
			m_Pickup->Present();
		}
	}
	void Item::SetPickup(Pickup* pickup)
	{
		if (m_Pickup == nullptr)
		{
			m_Pickup = pickup;
		}
		else
		{
			std::string message = "Error trying to set ItemBoxTile pickup when one is already set";
			Log::Error(false, Log::Verbosity_Debug, message);
		}
	}

	Pickup* Item::GetPickup()
	{
		return m_Pickup;
	}
}