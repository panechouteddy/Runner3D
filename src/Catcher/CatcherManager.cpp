#include "pch.h"
#include "CatcherManager.h"

#include "Player.h"
#include "BallManager.h"

#include "Collider.h"

void CatcherManager::Init()
{
	GameManager::Init();

	//floor
	donut = new sr::Donut(0.525f, 0.05f);
	donut->SetScale({5, 1, 5});

	sr::Texture* texture = new sr::Texture("res/Textures/wood.jpg");
	donut->SetTexture(*texture);

	m_pPlayer = new Player();
	m_pPlayer->SetGameManager(this);
	m_pPlayer->Init();
	std::cout << "player create" << std::endl;

	m_pBallManager = new BallManager();
	m_pBallManager->Init(this);

	mText = new sr::Text();
	mText->SetText(std::to_wstring(mScore));
	mText->SetPosition({460.0f, 235.0f});
	mText->SetColor(gce::Color::White);
	mText->SetOpacity(100);

	mTextLife = new sr::Text();
	mTextLife->SetText(std::to_wstring(mLife));
	mTextLife->SetPosition({ 900, 0 });
	mTextLife->SetColor(gce::Color::Red);
	mTextLife->SetOpacity(100);
}

void CatcherManager::Update(float deltaTime)
{
	mText->SetText(std::to_wstring(mScore));
	mTextLife->SetText(std::to_wstring(mLife));

	if (mLife <= 0)
	{
		if (isLoosed == false)
		{
			isLoosed = true;
			mEndText = new sr::Text();
			mEndText->SetText(L"Votre score : " + std::to_wstring(mScore));
			mEndText->SetPosition({ 300,200 });
			mEndText->SetColor(gce::Color::Black);
			mEndText->SetOpacity(100);
		}
	}
	else
	{
		GameManager::Update(deltaTime);

		m_pBallManager->Update(deltaTime);

		if (sr::GetKeyDown(sr::Keyboard::SPACE))
		{
			Pause();
		}
	}	
}

void CatcherManager::Draw(sr::Window& window)
{
	if (isLoosed == false)
	{
		GameManager::Draw(window);

		window.Draw(*donut);
		window.DrawText(*mText);
		window.DrawText(*mTextLife);
	}
	else
	{
		window.DrawText(*mEndText);
	}
}

void CatcherManager::CleanAll()
{
	GameManager::CleanAll();
	delete m_pBallManager;
	delete donut;	
	delete mText;	
	delete mTextLife;
	delete mEndText;
}

void CatcherManager::Pause()
{
	isPaused = !isPaused;
}

