#pragma once
#include "Entity.h"
#include "Collider.h"

class ShuffleManager;

class EnnemyBot : public Entity, public Collider
{
	ShuffleManager* m_pGameManager = nullptr;

	gce::Vector3f32 oldPos;
	gce::Vector3f32 mVelocity = { 0, 0, 0 };

	float speed = 4.f;

	sr::Geometry* m_pPalette;
	gce::Vector3f32 offset;

public:
	void Init() override;
	void SetGameManager(ShuffleManager* gameManager);
	void SetPalette(sr::Geometry* palette);

	void Update(float deltaTime) override;

	void GoToPalette(float deltaTime);
	void OnCollision() override;
};

