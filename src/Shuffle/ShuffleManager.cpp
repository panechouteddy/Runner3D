#include "pch.h"
#include "ShuffleManager.h"

#include "Player.h"
#include "Puck.h"
#include "EnnemyBot.h"

void ShuffleManager::Init()
{
	GameManager::Init();

	Player* player = new Player();
	player->Init();
	player->SetGameManager(this);

	Puck* puck = new Puck();
	puck->Init();
	puck->SetGameManager(this);

	EnnemyBot* ennemyBot = new EnnemyBot();
	ennemyBot->Init();
	ennemyBot->SetGameManager(this);
	ennemyBot->SetPalette(puck->m_pGeo);

	sr::HideMouseCursor();

	//Bordure
	sr::Texture* texture = new sr::Texture("res/Textures/wood.jpg");

	sr::Geometry* bord1 = new sr::Cube;
	bord1->SetPosition({ 3.8f, 0, 0 });
	bord1->SetScale({ 1, 0.1f, 12 });
	bord1->SetTexture(*texture);

	sr::Geometry* bord2 = new sr::Cube;
	bord2->SetPosition({ -3.8f, 0, 0 });
	bord2->SetScale({ 1, 0.1f, 12 });
	bord2->SetTexture(*texture);

	mBords.push_back(bord1);
	mBords.push_back(bord2);

	//Text
	mScorePlayer = new sr::Text();
	mScorePlayer->SetText(std::to_wstring(playerScore));
	mScorePlayer->SetPosition({ 0, 0 });
	mScorePlayer->SetColor(gce::Color::Magenta);
	mScorePlayer->SetOpacity(100);

	mScoreBot = new sr::Text();
	mScoreBot->SetText(std::to_wstring(ennemyBotScore));
	mScoreBot->SetPosition({ 900, 0 });
	mScoreBot->SetColor(gce::Color::Yellow);
	mScoreBot->SetOpacity(100);
}

void ShuffleManager::Update(float deltaTime)
{
	if (isFinished == false)
	{
		mScorePlayer->SetText(std::to_wstring(playerScore));
		mScoreBot->SetText(std::to_wstring(ennemyBotScore));

		if (isPaused == false)
		{
			GameManager::Update(deltaTime);

		}

		if (sr::GetKeyDown(sr::Keyboard::SPACE))
		{
			isPaused = !isPaused;
		}

		if (ennemyBotScore >= 5 || playerScore >= 5)
		{
			isFinished = true;
		}
	}
}

void ShuffleManager::Draw(sr::Window& window)
{
	if (isFinished == false)
	{
		GameManager::Draw(window);

		for (sr::Geometry* geo : mBords)
		{
			window.Draw(*geo);
		}

		window.DrawText(*mScorePlayer);
		window.DrawText(*mScoreBot);
	}
}

void ShuffleManager::CleanAll()
{
	GameManager::CleanAll();
	for (sr::Geometry* geo : mBords)
	{
		delete geo;
	}
	delete mScorePlayer;
	delete mScoreBot;
}
