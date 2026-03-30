#include "pch.h"
#include "EnnemyBot.h"

#include "ShuffleManager.h"

void EnnemyBot::Init()
{
	m_geo = new sr::Cylinder;
	m_geo->SetColor({ 0, 255, 0 });
	m_geo->SetPosition({ 0, 0, 4 });
	m_geo->SetScale({ 0.7f, 0.1f, 0.7f });

	mRayon = 0.35f;
	m_pGeo = m_geo;

	m_pVelocity = &mVelocity;

	oldPos = m_geo->GetPosition();
}

void EnnemyBot::SetGameManager(ShuffleManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void EnnemyBot::SetPalette(sr::Geometry* palette)
{
	offset = { 0, 0, -0.3f };
	m_pPalette = palette;
}

void EnnemyBot::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		GoToPalette(deltaTime);

		gce::Vector3f32 pos = m_geo->GetPosition();

		//mVelocity *= 0.95f;

		gce::Vector3f32 newPos = pos + mVelocity;

		float limX = 3.f;

		if (newPos.x > limX)
		{
			newPos.x = limX;
		}
		else if (newPos.x < -limX)
		{
			newPos.x = -limX;
		}

		float limZ = 5.5f;

		if (newPos.z > limZ)
		{
			newPos.z = limZ;
		}
		else if (newPos.z < 0)
		{
			newPos.z = 0;
		}

		m_geo->SetPosition(newPos);
	}
}

void EnnemyBot::GoToPalette(float deltaTime)
{
	gce::Vector3f32 pos1 = m_pPalette->GetPosition();
	gce::Vector3f32 pos2 = m_geo->GetPosition();

	gce::Vector3f32 dir = pos1 - pos2;

	//Normale
	float dist = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z));

	float diff = 1;

	if (dist != speed)
	{
		diff = speed / dist;
	}

	m_geo->SetPosition(m_geo->GetPosition() + dir * deltaTime * diff);
}

void EnnemyBot::OnCollision()
{
}
