#pragma once
#include "GameManager.h"

class ShuffleManager : public GameManager
{
	std::vector<sr::Geometry*> mBords;

	int playerScore = 0;
	int ennemyBotScore = 0;

	sr::Text* mScorePlayer;
	sr::Text* mScoreBot;

public:
	void Init() override;
	void Update(float deltaTime) override;
	void Draw(sr::Window& window) override;

	void CleanAll() override;

	void PlayerScore() { playerScore++; }
	void BotScore() { ennemyBotScore++; }
};

