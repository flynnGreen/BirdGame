#include "EyeFly.h"
#include "Constants.h"


namespace GameDev2D
{
	EyeFly::EyeFly(const Vector2& startingPosition, float displacementY) : Enemy(),
		m_EyeFly(nullptr),
		m_StartingPosition(startingPosition),
		m_EndPointRight(startingPosition + Vector2(0.0f, fabsf(displacementY))),
		m_EndPointLeft(startingPosition - Vector2(0.0f, fabsf(displacementY))),
		m_InitialDirectionX(displacementY / fabsf(displacementY))
	{
		//Create the EyeFly AnimatedSprite
		m_EyeFly = new AnimatedSprite("Assets");
		m_EyeFly->AddFrame("Enemy1-1");
		m_EyeFly->AddFrame("Enemy1-2");
		m_EyeFly->AddFrame("Enemy1-3");
		m_EyeFly->SetFrameSpeed(15.0f);
		m_EyeFly->SetDoesLoop(true);
		m_EyeFly->SetAnchor(0.5f, 0.5f);
		m_EyeFly->AttachTo(this);

		//Add the collider
		CollisionFilter filter(ENEMY_COLLISION_FILTER, PLAYER_COLLISION_FILTER | ENEMY_COLLISION_FILTER);
		AddAxisAlignedRectangleCollider(GetWidth(), GetHeight(), Collider::Static, filter);

		//Reset the EyeFly
		Reset();
	}

	EyeFly::~EyeFly()
	{
		SafeDelete(m_EyeFly);
	}

	Enemy::Type EyeFly::GetType()
	{
		return Enemy::EyeFly;
	}

	void EyeFly::Update(double delta)
	{
		//EyeFly moving Right
		if (GetScale().x == 1.0f)
		{
			//Calculate the displacement for this frame
			float displacementY = EYE_SPEED * delta;
			Translate(Vector2(0.0f, displacementY));

			//Turn around
			if (GetPosition().y > m_EndPointRight.y)
			{
				Flip();
			}
		}
		//EyeFly moving Left
		else if (GetScale().x == -1.0f)
		{
			//Calculate the displacement for this frame
			float displacementY = -EYE_SPEED * delta;
			Translate(Vector2(0.0f, displacementY));

			//Turn around
			if (GetPosition().y < m_EndPointLeft.y)
			{
				Flip();
			}
		}
	}

	void EyeFly::Draw(SpriteBatch* spriteBatch)
	{
		spriteBatch->Draw(m_EyeFly);
	}

	void EyeFly::Reset()
	{
		SetPosition(m_StartingPosition);
		SetIsActive(this->IsActive());
		SetScaleX(m_InitialDirectionX);
	}

	float EyeFly::GetWidth()
	{
		return m_EyeFly->GetWidth();
	}

	float EyeFly::GetHeight()
	{
		return m_EyeFly->GetHeight();
	}

	void EyeFly::Flip()
	{
		float scaleX = GetScale().x;
		scaleX *= -1.0f;
		SetScaleX(scaleX);
	}
}