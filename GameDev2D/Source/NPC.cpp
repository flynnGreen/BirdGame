#include "NPC.h"
#include "Constants.h"


namespace GameDev2D
{
	NPC::NPC(const Vector2& startingPosition, float displacementX) : Enemy(),
		m_NPC(nullptr),
		m_StartingPosition(startingPosition),
		m_EndPointRight(startingPosition + Vector2(fabsf(displacementX), 0.0f)),
		m_EndPointLeft(startingPosition - Vector2(fabsf(displacementX), 0.0f)),
		m_InitialDirectionX(displacementX / fabsf(displacementX)),
		m_ChangedDirectionTimer(NPC_COLLISION_IGNORE_DURATION)
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

	NPC::~NPC()
	{
		SafeDelete(m_NPC);
	}

	Enemy::Type NPC::GetType()
	{
		return Enemy::NPC;
	}

	void NPC::Update(double delta)
	{
		m_ChangedDirectionTimer.Update(delta);

		//NPC turning around
		if (GetScale().x == 1.0f)
		{
			//Turn around
			if (GetPosition().x > m_EndPointRight.x)
			{
				if (m_ChangedDirectionTimer.IsDone() == true)
				{
					Flip();
				}
			}
		}
		//NPC moving Left
		else if (GetScale().x == -1.0f)
		{
			//Turn around
			if (GetPosition().x < m_EndPointLeft.x)
			{
				if (m_ChangedDirectionTimer.IsDone() == true)
				{
					Flip();
				}
			}
		}
	}

	void NPC::Draw(SpriteBatch* spriteBatch)
	{
		if (this->IsActive() == true)
		{
			spriteBatch->Draw(m_NPC);
		}
	}

	void NPC::Reset()
	{
		SetPosition(m_StartingPosition);
		SetIsActive(this->IsActive());
		SetScaleX(m_InitialDirectionX);
		m_ChangedDirectionTimer.Restart();
	}

	void NPC::CollisionDetected(CollisionEvent* collisionEvent)
	{
		if (collisionEvent->a->GetGameObject() == this)
		{
			if (collisionEvent->b->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->b->GetGameObject());
				if (enemy->GetType() == Enemy::NPC)
				{
					if (m_ChangedDirectionTimer.IsRunning() == false)
					{
						SetIsActive(false);
						m_ChangedDirectionTimer.Stop();
					}
				}
			}
		}
		else if (collisionEvent->b->GetGameObject() == this)
		{
			if (collisionEvent->a->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->a->GetGameObject());
				if (enemy->GetType() == Enemy::NPC)
				{
					if (m_ChangedDirectionTimer.IsRunning() == false)
					{
						SetIsActive(false);
						m_ChangedDirectionTimer.Stop();
					}
				}
			}
		}
	}

	float NPC::GetWidth()
	{
		return m_NPC->GetWidth();
	}

	float NPC::GetHeight()
	{
		return m_NPC->GetHeight();
	}

	void NPC::Flip()
	{
		float scaleX = GetScale().x;
		scaleX *= -1.0f;
		SetScaleX(scaleX);
	}
}