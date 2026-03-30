#include "pch.h"
#include "BallManager.h"
#include "Ball.h"
#include "CatcherManager.h"

void BallManager::Update(float deltaTime)
{
	if (m_pGameManager->GetPauseStatus() == false)
		cooldownProgress -= deltaTime;

	if (cooldownProgress <= 0)
	{
		cooldownProgress = cooldownTime;

		SpawnBall();
	}
}

void BallManager::SpawnBall()
{
	int range = 360 - 0 + 1;

	int value = rand() %  range;

	Ball* ball = new Ball();

	ball->Init();
	ball->SetGameManager(m_pGameManager);
	ball->SetPosition({2.5f, 10, 0});

	GameManager::Rotate(value, ball->GetGeo(), { 0, 10, 0 });
}
