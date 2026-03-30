#include "pch.h"
#include "RunnerScene.h"
#include "App.h"
#include "Ressources.h"

#include "Tile.h"
#include "RandomConfigGenerator.h"

#include "Controller.h"
#include "RunnerCamera.h"
#include "SceneManager.h"

#include "StaticEnnemi.h"
#include "MoveEnnemy.h"
#include "CrazyFrogEnnemy.h"

void RunnerScene::Clear()
{
	Scene::Clear();

	m_TileGenerator.Clear();

	delete m_pController;
	m_pController = nullptr;
}

void RunnerScene::InitCamSettings()
{
	auto pCam = App::GetRunnerCamera();
	pCam->SetFOV(gce::PI / 2.0f);
	pCam->SetCameraPlane(0.1f, 1000.f);
}

void RunnerScene::InitTransitions()
{
	for (int i = 0; i < TAG_COUNT; i++)
	{
		for (int j = 0; j < TAG_COUNT; j++)
		{
			m_Interactions[i][j] = false;
		}
	}

	SetTransitionBetween(Tag::TPlayer, Tag::TFloor, true);
	SetTransitionBetween(Tag::TPlayer, Tag::TCoin, true);
	SetTransitionBetween(Tag::TPlayer, Tag::TWall, true);
	SetTransitionBetween(Tag::TPlayer, Tag::TEnnemy, true);
	SetTransitionBetween(Tag::TPlayer, Tag::TPowerUp, true);
}

void RunnerScene::HandleScore()
{
	if (m_pCharacter->HasLost())
		return;

	if (m_Progress_Score < 0)
	{
		m_Progress_Score = 0.01f;
		m_Score++;
	}
	else
	{
		m_Progress_Score -= App::GetDeltaTime();
	}
}

void RunnerScene::UIManager()
{
	DrawText(L" Score : " + std::to_wstring(m_Score), { 0.f, 0.f }, gce::Color::Black);
	DrawText(L" Coins : " + std::to_wstring(m_Coins_Number), { 0.f, 100.f }, gce::Color::Yellow);
}

void RunnerScene::FPSModManager()
{
	RunnerCamera* pCam = App::GetRunnerCamera();

	if (m_FpsMod)
	{
		pCam->FollowEntity(m_pCharacter, { 0.f, 0.f, 0.f }, { 1, 1, 1 });
		pCam->SetRotation({ 0, 0, 0 });
	}
	else
	{
		const float posY = 75.f;

		pCam->SetPosition({ 0.f, posY, pCam->GetPosition().z });
		pCam->FollowEntity(m_pCharacter, { 0.f, 75.f, -15.f }, { 0, 0, 1 });
		pCam->SetRotation({ 50.f, 0, 0 });
	}
}

void RunnerScene::SetTransitionBetween(int tag1, int tag2, bool state)
{
	m_Interactions[tag1][tag2] = state;
	m_Interactions[tag2][tag1] = state;
}

bool RunnerScene::IsAllowedToCollide(int tag1, int tag2)
{
	if (m_Interactions[tag1][tag2] == true)
		return true;

	return false;
}

void RunnerScene::Init()
{
	m_Score = 0;
	m_Progress_Score = 0.f;
	m_Coins_Number = 0;

	InitCamSettings();

	m_pCharacter = new Character();
	Add(m_pCharacter);

	m_pController = new Controller();


	m_TileGenerator.InitFirst();
	m_RCG = new RandomConfigGenerator(&m_TileGenerator);

	for (int i = 0; i < 5; i++)
	{
		m_RCG->GenerateRandomConfig();
	}

	InitTransitions();
}

void RunnerScene::Update()
{
	float dt = App::GetDeltaTime();

	PauseKeyManager();

	UIManager();
	FPSModManager();

	if (quit)
	{
		App::Get()->GetSceneManager()->ChangeScene(SceneName::Menu);
		return;
	}

	if (isPaused)
	{
		return;
	}

	m_pController->Update();

	Scene::Update();

	gce::Vector3f32 camPos = App::GetRunnerCamera()->GetPosition();

	if (auto lastTile = m_TileGenerator.GetLastTile())
	{
		if (lastTile->GetCenter().z <= camPos.z - Tile_Size * 2.f)
		{
			m_TileGenerator.DestroyLastTile();
			m_RCG->GenerateRandomConfig();
		}
	}

	HandleScore();
}