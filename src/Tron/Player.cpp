#include "pch.h"
#include "Player.h"

#include "TronManager.h"
#include "Trail.h"

void Player::Init()
{
	m_Direction = Vector3f32(-1.f, 0.f, 0.f);
	m_Speed = 5;
	m_Type = 0;
	mRayon = 1.f;
	m_PlayerID = 1;

	m_geo = new sr::Cylinder;
	m_geo->SetColor({ 0, 0, 255 });
	m_geo->SetPosition({ -10.f, 0, 0 });
	m_geo->SetScale({ 1.f, 0.1f, 1.f });
	m_pGeo = m_geo;

	m_LastTrailPos = m_geo->GetPosition();
}

void Player::SetGameManager(TronManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void Player::OnCollision()
{
	if (m_PlayerID == 1)
	{
		m_pGameManager->Player2Win();
	}
	else
	{
		m_pGameManager->Player1Win();
	}
}

void Player::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		m_Position = m_geo->GetPosition();
		m_TrailDelay -= deltaTime;
		
		if (sr::GetKeyDown(left) && m_Direction.x != 1.f)
		{
			m_pGameManager->AddTrail(this);
			m_LastTrailPos = m_Position;
			m_Direction = Vector3f32(-1, 0, 0);
		}
		else if (sr::GetKeyDown(right) && m_Direction.x != -1.f)
		{
			m_pGameManager->AddTrail(this);
			m_LastTrailPos = m_Position;
			m_Direction = Vector3f32(1, 0, 0);
		}
		else if (sr::GetKeyDown(up) && m_Direction.z != -1.f)
		{
			m_pGameManager->AddTrail(this);
			m_LastTrailPos = m_Position;
			m_Direction = Vector3f32(0, 0, 1);
		}
		else if (sr::GetKeyDown(down) && m_Direction.z != 1.f)
		{
			m_pGameManager->AddTrail(this);
			m_LastTrailPos = m_Position;
			m_Direction = Vector3f32(0, 0, -1);
		}

		//Add trail constant
		if (m_TrailDelay <= 0.f)
		{
			m_pGameManager->AddTrail(this);
			m_LastTrailPos = m_Position;
			m_TrailDelay = 0.5f;
		}

		// Ajouter le lose screen
		if (m_Position.x > 34.0f || m_Position.x < -34.0f)
		{
			OnCollision();
		}

		if (m_Position.z > 19.0f || m_Position.z < -19.0f)
		{
			OnCollision();
		}


		m_pGeo->SetPosition(m_Position + m_Direction * deltaTime * m_Speed);
	}
}

void Player::SetPlayer2()
{
	m_Direction = Vector3f32(1, 0, 0);
	m_geo->SetColor({ 1, 0, 0 });
	m_geo->SetPosition({ 10.f, 0, 0 });
	m_PlayerID = 2;

	m_LastTrailPos = m_geo->GetPosition();

	up = sr::Keyboard::Z;
	down = sr::Keyboard::S;
	left = sr::Keyboard::Q;
	right = sr::Keyboard::D;
}
