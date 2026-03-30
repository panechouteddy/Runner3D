#pragma once
#include "Entity.h"
#include "Collider.h"

class TronManager;
class Player;

class Trail : public Entity, public Collider
{
	TronManager* m_pGameManager = nullptr;

public:
	
	void Init() override;
	void SetGameManager(TronManager* gameManager);
	
	void PlaceBehindPlayer(Player* pPlayer);

	void Update(float deltaTime) override {};

	void OnCollision() override {};	
};

