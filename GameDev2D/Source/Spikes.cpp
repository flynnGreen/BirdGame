#include "Spikes.h"
#include "Room.h"
#include "Level.h"
#include "Player.h"

namespace GameDev2D
{
	Spikes::Spikes(Room* room, Vector2 startPosition, Vector2 displacement, double duration) :
		GameObject(),
		m_Room(room),
		m_Collider(nullptr),
		m_Spikes(nullptr),
		m_StartPosition(startPosition),
		m_Displacement(displacement),
		m_Timer(duration)
	{

		m_Spikes = new SpriteAtlas("Assets");
		m_Spikes->UseFrame("Spikes");

		m_Spikes->SetAnchor(0.0f, 0.5f);
		m_Spikes->SetPosition((-GetWidth() * 0.5f), 0.0f);
		m_Spikes->AttachTo(this);

		CollisionFilter filter = CollisionFilter(SPIKES_COLLISION_FILTER, PLAYER_COLLISION_FILTER);
		m_Collider = AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Static, filter);

		SetPosition(m_StartPosition);

		m_Timer.SetDoesLoop(true);
		m_Timer.Start();
	}

	Spikes::~Spikes()
	{
		SafeDelete(m_Spikes);
	}

	void Spikes::Update(double delta)
	{
		m_Timer.Update(delta);

		float pct = m_Timer.GetPercentageElapsed();
		float radians = (2.0f * M_PI) * pct;
		Vector2 displacement = m_Displacement * sinf(radians);

		Vector2 position = m_StartPosition + displacement;
		Vector2 difference = position - GetPosition();

		SetPosition(position);

		Player* player = m_Room->GetLevel()->GetPlayer();

		if (player->GetCollider()->IsColliding(GetCollider()) == true)
		{
			player->Kill();
		}
	}

	void Spikes::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_Spikes);
	}

	void Spikes::Reset()
	{
	}

	float Spikes::GetWidth()
	{
		return SPIKES_WIDTH;
	}

	float Spikes::GetHeight()
	{
		return SPIKES_HEIGHT;
	}

	AxisAlignedRectangleCollider* Spikes::GetCollider()
	{
		return m_Collider;
	}
}