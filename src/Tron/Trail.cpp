#include "pch.h"
#include "Trail.h"

#include "TronManager.h"
#include "Player.h"
#include <iostream>

void Trail::Init()
{
	m_geo = new sr::Plane;
	m_geo->SetColor({ 0.f, 1.f, 0.f });

	m_Type = 1;
	m_pGeo = m_geo;
}

void Trail::SetGameManager(TronManager* gameManager)
{
	m_pGameManager = gameManager;
	
	m_pGameManager->AddEntity(this);
	m_pGameManager->AddCollider(this);
}

void Trail::PlaceBehindPlayer(Player* pPlayer)
{
	if (pPlayer->GetPlayerID() == 1)
	{
		m_geo->SetColor({ 0.f, 0.f, 1.f });
	}
	else
	{
		m_geo->SetColor({ 1.f, 0.f, 0.f });	
	}

	gce::Vector3f32 playerPos = pPlayer->GetPosition();
	gce::Vector3f32 lastTrailPos = pPlayer->GetLastTrailPos();
	gce::Vector3f32 playerDir = pPlayer->GetDirection();

	float offsetX = pPlayer->mRayon * playerDir.x;
	float offsetZ = pPlayer->mRayon * playerDir.z;

	float playerBackPosX = playerPos.x - offsetX;
	float playerBackPosZ = playerPos.z - offsetZ;

	float lengthX = abs(playerBackPosX - lastTrailPos.x);
	float lengthZ = abs(playerBackPosZ - lastTrailPos.z);

	m_geo->SetPosition({
		playerBackPosX - playerDir.x * (0.5f * lengthX),
		0.05f,
		playerBackPosZ - playerDir.z * (0.5f * lengthZ)
		});

	m_geo->SetScale({
		0.5f + lengthX * abs(playerDir.x),
		1.f,
		0.5f + lengthZ * abs(playerDir.z)
		});

	m_halfSize = { 
		lengthX* abs(playerDir.x) * 0.5f,
		0.f,
		lengthZ* abs(playerDir.z) * 0.5f
	};
}
