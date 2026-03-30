#include "pch.h"
#include "Puck.h"

#include "ShuffleManager.h"

void Puck::Init()
{
	m_geo = new sr::Cylinder();
	m_geo->SetColor({ 0, 0, 0 });
	m_geo->SetPosition({ 0, 0, 0 });
	m_geo->SetScale({ 0.6f, 0.1f, 0.6f });

	mRayon = 0.3f;
	m_pGeo = m_geo;

	m_pVelocity = &mVelocity;
	mOldPos = m_geo->GetPosition();
}

void Puck::SetGameManager(ShuffleManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddCollider(this);
	m_pGameManager->AddEntity(this);
}

void Puck::OnCollision()
{
}

void Puck::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		gce::Vector3f32 pos = m_geo->GetPosition();

		m_geo->SetPosition(pos + mVelocity);

		mVelocity = pos - mOldPos;
		mVelocity *= 0.99f;
		mOldPos = pos;

		float limX = 3.f;

		if (pos.x > limX)
		{
			m_geo->SetPosition({ limX * 0.99f, pos.y, pos.z });
			mVelocity.x = -mVelocity.x;
		}
		else if (pos.x < -limX)
		{
			m_geo->SetPosition({ -limX * 0.99f, pos.y, pos.z });
			mVelocity.x = -mVelocity.x;
		}

		float limZ = 5.5f;

		if (pos.z > limZ)
		{
			m_geo->SetPosition({ 0, 0, 0 });
			mVelocity = { 0, 0, 0 };
			mOldPos = { 0, 0, 0 };

			m_pGameManager->PlayerScore();
		}
		else if (pos.z < -limZ)
		{
			m_geo->SetPosition({ 0, 0, 0 });
			mVelocity = { 0, 0, 0 };
			mOldPos = { 0, 0, 0 };
			m_pGameManager->BotScore();
		}
	}
}