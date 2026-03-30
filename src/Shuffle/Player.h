#pragma once

#include "Entity.h"
#include "Collider.h"

class GameManager;
class ShuffleManager;

class Player : private Entity, public Collider
{
	ShuffleManager* m_pGameManager;

	gce::Vector3f32 mOldPos;
	gce::Vector3f32 mVelocity = { 0, 0, 0 };

public:
	void Init() override;
	void SetGameManager(ShuffleManager* gameManager);

	void OnCollision() override;

	void Update(float deltaTime) override;
};

