#include "SexyFish.h"
#include "Constants.h"


namespace GameDev2D
{
	SexyFish::SexyFish(const Vector2& startingPosition, float displacementX) : Enemy(),
		m_SexyFish(nullptr),
		m_StartingPosition(startingPosition),
		m_EndPointRight(startingPosition + Vector2(fabsf(displacementX), 0.0f)),
		m_EndPointLeft(startingPosition - Vector2(fabsf(displacementX), 0.0f)),
		m_InitialDirectionX(displacementX / fabsf(displacementX)),
		m_ChangedDirectionTimer(SEXY_COLLISION_IGNORE_DURATION)
	{
		//Create the SexyFish AnimatedSprite
		m_SexyFish = new AnimatedSprite("Assets");
		m_SexyFish->AddFrame("Enemy3-1");
		m_SexyFish->AddFrame("Enemy3-2");
		m_SexyFish->AddFrame("Enemy3-3");
		m_SexyFish->AddFrame("Enemy3-4");
		m_SexyFish->AddFrame("Enemy3-5");
		m_SexyFish->AddFrame("Enemy3-6");
		m_SexyFish->SetFrameSpeed(10.0f);
		m_SexyFish->SetDoesLoop(true);
		m_SexyFish->SetAnchor(0.5f, 0.5f);
		m_SexyFish->AttachTo(this);

		//Add the collider
		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER | ENEMY_COLLISION_FILTER);
		AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Dynamic, filter);

		//Reset the SexyFish
		Reset();
	}

	SexyFish::~SexyFish()
	{
		SafeDelete(m_SexyFish);
	}

	Enemy::Type SexyFish::GetType()
	{
		return Enemy::SexyFish;
	}

	void SexyFish::Update(double delta)
	{
		m_ChangedDirectionTimer.Update(delta);

		//SexyFish moving Right
		if (GetScale().x == 1.0f)
		{
			//Calculate the displacement for this frame
			float displacementX = SEXY_SPEED * delta;
			Translate(Vector2(displacementX, 0.0f));

			//Turn around
			if (GetPosition().x > m_EndPointRight.x)
			{
				Flip();
			}
		}
		//SexyFish moving Left
		else if (GetScale().x == -1.0f)
		{
			//Calculate the displacement for this frame
			float displacementX = -SEXY_SPEED * delta;
			Translate(Vector2(displacementX, 0.0f));

			//Turn around
			if (GetPosition().x < m_EndPointLeft.x)
			{
				Flip();
			}
		}
	}

	void SexyFish::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_SexyFish);
	}

	void SexyFish::Reset()
	{
		SetPosition(m_StartingPosition);
		SetIsActive(true);
		SetScaleX(m_InitialDirectionX);
		m_ChangedDirectionTimer.Restart();
	}

	void SexyFish::CollisionDetected(CollisionEvent* collisionEvent)
	{
		if (collisionEvent->a->GetGameObject() == this)
		{
			if (collisionEvent->b->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->b->GetGameObject());
				if (enemy->GetType() == Enemy::SexyFish)
				{
					if (m_ChangedDirectionTimer.IsRunning() == false)
					{
						Flip();
						m_ChangedDirectionTimer.Restart();
					}
				}
			}
		}
		else if (collisionEvent->b->GetGameObject() == this)
		{
			if (collisionEvent->a->GetFilter().categoryBits == ENEMY_COLLISION_FILTER)
			{
				Enemy* enemy = static_cast<Enemy*>(collisionEvent->a->GetGameObject());
				if (enemy->GetType() == Enemy::SexyFish)
				{
					if (m_ChangedDirectionTimer.IsRunning() == false)
					{
						Flip();
						m_ChangedDirectionTimer.Restart();
					}
				}
			}
		}
	}

	float SexyFish::GetWidth()
	{
		return m_SexyFish->GetWidth();
	}

	float SexyFish::GetHeight()
	{
		return m_SexyFish->GetHeight();
	}

	void SexyFish::Flip()
	{
		float scaleX = GetScale().x;
		scaleX *= -1.0f;
		SetScaleX(scaleX);
	}
}