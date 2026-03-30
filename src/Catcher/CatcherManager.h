#pragma once

#include "GameManager.h"

class Player;
class BallManager;

class CatcherManager : public GameManager
{
	Player* m_pPlayer;
	BallManager* m_pBallManager;

	sr::Geometry* donut;

	sr::Text* mText;
	int mScore = 0;

	sr::Text* mTextLife;
	int mLife = 3;

	sr::Text* mEndText;

public:

	void Init() override;
	void Update(float deltaTime) override;
	void Draw(sr::Window& window) override;
	void CleanAll() override;

	void Pause();
	void PlayerScore() { mScore++; };
	void PlayerMiss() { mLife--; }
};

