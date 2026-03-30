#pragma once
#include "Entity.h"
#include "Collider.h"

class ShuffleManager;

class Puck : public Entity, public Collider
{
	ShuffleManager* m_pGameManager = nullptr;

	gce::Vector3f32 mOldPos;
	gce::Vector3f32 mVelocity = { 0, 0, 0 };

public:
	void Init() override;
	void SetGameManager(ShuffleManager* gameManager);

	void OnCollision() override;

	void Update(float deltaTime) override;
};

