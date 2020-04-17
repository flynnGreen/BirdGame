#include "NPCend.h"
#include "Constants.h"


namespace GameDev2D
{
	NPCend::NPCend(const Vector2& startingPosition) : Enemy(),
		m_NPC(nullptr),
		m_StartingPosition(startingPosition),
		m_ChangedDirectionTimer(Math::RandomInt(2, 6))
	{
		//Create the NPC AnimatedSprite
		m_NPC = new SpriteAtlas("Assets");
		m_NPC->UseFrame("NPC");
		m_NPC->SetAnchor(0.5f, 0.5f);
		m_NPC->AttachTo(this);

		//Add the collider
		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER | ENEMY_COLLISION_FILTER);
		AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Static, filter);

		//Reset the NPC
		Reset();
	}

	NPCend::~NPCend()
	{
		SafeDelete(m_NPC);
	}

	Enemy::Type NPCend::GetType()
	{
		return Enemy::NPCend;
	}

	void NPCend::Update(double delta)
	{
		m_ChangedDirectionTimer.Update(delta);

		//NPC turning around
		if (m_ChangedDirectionTimer.IsDone() == true)
		{
			Flip();
		}
	}

	void NPCend::Draw(SpriteBatch* spriteBatch)
	{
		if (this->IsActive() == true)
		{
			spriteBatch->Draw(m_NPC);
		}
	}

	void NPCend::Reset()
	{
		SetPosition(m_StartingPosition);
		SetIsActive(this->IsActive());
		SetScaleX(m_InitialDirectionX);
		m_ChangedDirectionTimer.Restart();
	}

	float NPCend::GetWidth()
	{
		return m_NPC->GetWidth();
	}

	float NPCend::GetHeight()
	{
		return m_NPC->GetHeight();
	}

	void NPCend::Flip()
	{
		float scaleX = GetScale().x;
		scaleX *= -1.0f;
		SetScaleX(scaleX);
		m_ChangedDirectionTimer.Restart();
	}
}