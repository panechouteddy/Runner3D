#pragma once

class Ball;
class CatcherManager;

class BallManager
{
	CatcherManager* m_pGameManager;

	float cooldownTime = 2;
	float cooldownProgress = 2.0f;

public:
	void Init(CatcherManager* gameManager) { m_pGameManager = gameManager; };

	void Update(float deltaTime);
	void SpawnBall();
};

