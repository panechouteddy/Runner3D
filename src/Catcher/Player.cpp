#include "pch.h"
#include "Player.h"

#include "CatcherManager.h"

void Player::Init()
{
	m_geo = new sr::Sphere();
	m_geo->SetColor({ 0, 0, 255 });
	m_geo->SetPosition({2.5f, 0.5f, 0});

	mRayon = 0.5f;
	mType = 0;
	m_pGeo = m_geo;
}

void Player::SetGameManager(CatcherManager* gameManager)
{
	m_pGameManager = gameManager;

	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void Player::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
	{
		if (sr::GetKey(sr::Keyboard::LEFT_ARROW))
			GameManager::Rotate(-0.5, m_geo, { 0, 0.5f, 0 });

		if (sr::GetKey(sr::Keyboard::RIGHT_ARROW))
			GameManager::Rotate(0.5, m_geo, {0, 0.5f, 0});
	}
}
