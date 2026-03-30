#include "pch.h"
#include "Player.h"

#include "ShuffleManager.h"

void Player::Init()
{
	m_geo = new sr::Cylinder;
	m_geo->SetColor({ 0, 0, 255 });
	m_geo->SetPosition({ 0, 0, -4 });
	m_geo->SetScale({ 0.7f, 0.1f, 0.7f });

	mRayon = 0.35f;
	m_pGeo = m_geo;

	m_pVelocity = &mVelocity;

	mOldPos = m_geo->GetPosition();
}

void Player::SetGameManager(ShuffleManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void Player::OnCollision()
{
}

void Player::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		gce::Vector3f32 pos = m_geo->GetPosition();
		gce::Vector3f32 newPos = { ((float32)sr::GetMousePosition().x - 1920 / 4) * 0.02f, 0, ((float32)-sr::GetMousePosition().y + 1080 / 4) * 0.02f };

		mVelocity = pos - mOldPos;
		mOldPos = pos;

		float limX = 3.f;

		if (newPos.x > limX)
		{
			newPos.x = limX;
			mVelocity.x = -mVelocity.x;
		}
		else if (newPos.x < -limX)
		{
			newPos.x = -limX;
			mVelocity.x = -mVelocity.x;
		}

		float limZ = 5.5f;

		if (newPos.z > 0)
		{
			newPos.z = 0;
			mVelocity.z = -mVelocity.z;
		}
		else if (newPos.z < -limZ)
		{
			newPos.z = -limZ;
			mVelocity.z = -mVelocity.z;
		}

		m_geo->SetPosition(newPos);
	}
}
