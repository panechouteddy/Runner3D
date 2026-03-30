#include "pch.h"
#include "GameManager.h"

#include "Entity.h"
#include "Collider.h"

#include "PhysicManager.h"

void GameManager::Init()
{
	m_pPhysicManager = new PhysicManager;
}

void GameManager::Draw(sr::Window& window)
{
	for (Entity* entity : mEntity)
	{
		window.Draw(*entity->m_geo);
	}
}

void GameManager::Update(float deltaTime)
{
	for (Entity* entity : mEntity)
	{
		entity->Update(deltaTime);
	}

	m_pPhysicManager->CheckCollision(mCollider);
}

void GameManager::AddEntity(Entity* entity)
{
	mEntity.push_back(entity);
}

void GameManager::RemoveEntity(Entity* entity)
{
	bool found = false;

	int i = 0;

	while (found == false && i < mEntity.size())
	{
		if (mEntity[i] == entity)
		{
			found = true;
			mEntity.erase(mEntity.begin() + i);
		}

		i++;
	}
}

void GameManager::AddCollider(Collider* collider)
{
	mCollider.push_back(collider);
}

void GameManager::RemoveCollider(Collider* collider)
{
	bool found = false;

	int i = 0;

	while (found == false && i < mCollider.size())
	{
		if (mCollider[i] == collider)
		{
			found = true;
			mCollider.erase(mCollider.begin() + i);
		}

		i++;
	}
}

void GameManager::CleanAll()
{
	for (Entity* entity : mEntity)
	{
		delete entity;
	}
	delete m_pPhysicManager;
}

void GameManager::Rotate(float angle, sr::Geometry* pGeo, gce::Vector3f32 centre)
{
	float angleRadiant = angle * gce::PI / 180;

	Vector3f32 dir = pGeo->GetPosition() - centre;

	float x = dir.x * gce::Cos(angleRadiant) - dir.z * gce::Sin(angleRadiant);
	float z = dir.x * gce::Sin(angleRadiant) + dir.z * gce::Cos(angleRadiant);

	pGeo->SetPosition({ x, pGeo->GetPosition().y, z});
}


