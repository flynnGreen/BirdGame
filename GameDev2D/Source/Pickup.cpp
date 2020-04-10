#include "Pickup.h"
#include "Constants.h"


namespace GameDev2D
{
	Pickup::Pickup(const Vector2& startingPosition) : GameObject(),
		m_StartingPosition(startingPosition),
		m_Timer(ITEM_BOX_SCALE_TIMER * 2.0),
		m_State(Hidden)
	{
		Reset();
	}

	Pickup::~Pickup()
	{
	}

	void Pickup::Update(double delta)
	{
		if (m_State == Pickup::Animating)
		{
			m_Timer.Update(delta);
			Vector2 maxDisplacement(0.0f, HALF_TILE_SIZE + GetHeight() * 0.5f);
			Vector2 displacement = maxDisplacement * m_Timer.GetPercentageElapsed();
			SetPosition(m_StartingPosition + displacement);

			if (m_Timer.IsDone() == true)
			{
				m_State == Pickup::Showing;
			}
		}
	}

	void Pickup::Draw(SpriteBatch* spriteBatch)
	{

	}

	void Pickup::Reset()
	{
		SetPosition(m_StartingPosition);
		m_Timer.Restart();

		m_State = Pickup::Hidden;

		SetIsActive(true);
	}

	void Pickup::Present()
	{
		if (m_State == Pickup::Hidden)
		{
			m_State = Pickup::Animating;
		}
	}

	void Pickup::Consume()
	{
		if (m_State == Pickup::Animating || m_State == Pickup::Showing)
		{
			m_State = Pickup::Consumed;
			SetIsActive(false);
		}
	}
}