#include "pch.h"

#include "TronManager.h"
#include "Player.h"
#include "Trail.h"

void TronManager::Init()
{
	GameManager::Init();
	sr::Texture* texture = new sr::Texture("res/Textures/wood.jpg");

	m_pWinText = new sr::Text;

	Player* player = new Player();
	player->Init();
	player->SetGameManager(this);

	Player* player2 = new Player();
	player2->Init();
	player2->SetGameManager(this);
	player2->SetPlayer2();

	m_pGameArea = new sr::Plane();
	m_pGameArea->SetPosition({ 0, -0.1f, 0 });
	m_pGameArea->SetScale({ 70, 0.1f, 40 });
	m_pGameArea->SetTexture(*texture);

	gce::Vector3f32 color = { 0.8f, 0.2f, 0.4f };

	sr::Geometry* bord1 = new sr::Plane;
	bord1->SetPosition({ 35.0f, 0, 0 });
	bord1->SetScale({ 1, 0.1f, 40 });
	bord1->SetColor(color);

	sr::Geometry* bord2 = new sr::Plane;
	bord2->SetPosition({ -35.0f, 0, 0 });
	bord2->SetScale({ 1, 1.f, 40 });
	bord2->SetColor(color);

	sr::Geometry* bord3 = new sr::Plane;
	bord3->SetPosition({ 0, 0, 20.0f });
	bord3->SetScale({ 70, 1.f, 1 });
	bord3->SetColor(color);

	sr::Geometry* bord4 = new sr::Plane;
	bord4->SetPosition({ 0, 0, -20.0f });
	bord4->SetScale({ 70, 1.f, 1 });
	bord4->SetColor(color);

	m_Borders.push_back(bord1);
	m_Borders.push_back(bord2);
	m_Borders.push_back(bord3);
	m_Borders.push_back(bord4);
}

void TronManager::Update(float deltaTime)
{
	if (isFinished)
		return;

	GameManager::Update(deltaTime);

	if (sr::GetKeyDown(sr::Keyboard::SPACE))
	{
		isPaused = !isPaused;
	}
}

void TronManager::Draw(sr::Window& window)
{
	if (isFinished)
	{
		window.DrawText(*m_pWinText);
		return;
	}

	GameManager::Draw(window);

	for (sr::Geometry* geo : m_Borders)
	{
		window.Draw(*geo);
	}
	window.Draw(*m_pGameArea);
}

void TronManager::CleanAll()
{
	GameManager::CleanAll();
	for (sr::Geometry* geo : m_Borders)
	{
		delete geo;
	}
	m_Borders.clear();
	delete m_pGameArea;
	delete m_pWinText;
}

void TronManager::Player1Win()
{
	m_pWinText->SetText(L"Victoire Joueur 1");

	isFinished = true;
}

void TronManager::Player2Win()
{
	m_pWinText->SetText(L"Victoire Joueur 2");

	isFinished = true;
}

void TronManager::AddTrail(Player* pPlayer)
{
	Trail* trail = new Trail();
	trail->Init();
	trail->SetGameManager(this);
	trail->PlaceBehindPlayer(pPlayer);
}
