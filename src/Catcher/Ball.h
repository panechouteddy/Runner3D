#pragma once

#include "Entity.h"
#include "Collider.h"

class CatcherManager;

class Ball : private Entity, private Collider
{
	float force = 0.0f;

	CatcherManager* m_pGameManager = nullptr;

public:
	void Init() override;
	void SetGameManager(CatcherManager* gameManager);

	void Update(float deltaTime) override;

	void OnCollision() override;

	void SetPosition(gce::Vector3f32 pos);

	sr::Geometry* GetGeo() { return m_geo; }
};

