#pragma once

#include "Entity.h"
#include "Collider.h"

class CatcherManager;

class Player : private Entity, public Collider
{
	CatcherManager* m_pGameManager = nullptr;

public:
	void Init() override;
	void SetGameManager(CatcherManager* gameManager);

	void Update(float deltaTime) override;
};

