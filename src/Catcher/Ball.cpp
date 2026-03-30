#include "pch.h"
#include "Ball.h"

#include "GameManager.h"
#include "CatcherManager.h"

void Ball::Init()
{
	m_geo = new sr::Sphere();
	m_geo->SetColor({ 255, 0, 0 });
	m_geo->SetScale({ 0.5f, 0.5f, 0.5f });

	mRayon = 0.25f;
	mType = 1;
	m_pGeo = m_geo;
}

void Ball::SetGameManager(CatcherManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void Ball::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		//gravitée
		m_geo->SetPosition(m_geo->GetPosition() + Vector3f32(0, -1, 0) * force * deltaTime);

		force += 9.81f * deltaTime / 2;

		if (m_geo->GetPosition().y <= 0)
		{
			m_pGameManager->PlayerMiss();

			m_pGameManager->RemoveEntity(this);
			m_pGameManager->RemoveCollider(this);
			delete  this;
		}
	}
}

void Ball::OnCollision()
{
	m_pGameManager->PlayerScore();

	m_pGameManager->RemoveEntity(this);
	m_pGameManager->RemoveCollider(this);
	delete  this;
}

void Ball::SetPosition(gce::Vector3f32 pos)
{
	m_geo->SetPosition(pos);
}
