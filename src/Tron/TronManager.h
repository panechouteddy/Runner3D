#pragma once
#include "GameManager.h"
#include "Player.h"

class TronManager : public GameManager
{
	std::vector<sr::Geometry*> m_Borders;
	sr::Geometry* m_pGameArea = nullptr;

	sr::Text* m_pWinText;

public:
	void Init() override;
	void Update(float deltaTime) override;
	void Draw(sr::Window& window) override;

	void CleanAll() override;

	void Player1Win();
	void Player2Win();

	void AddTrail(Player* pPlayer);
};

