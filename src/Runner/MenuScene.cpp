#include "pch.h"
#include "MenuScene.h"
#include "ButtonText.h"
#include "App.h"
#include "RunnerCamera.h"

void MenuScene::Clear()
{
	Scene::Clear();

	m_Buttons.clear();
}

void MenuScene::Init()
{
	auto pCam = App::GetRunnerCamera();

	pCam->SetPosition({ 0.f, 0.f, 0.f });

	index = 0;

	ButtonText* b1 = new ButtonText(L"Play", { -30.f, -40.f }, SceneName::Runner);
	Add(b1);
	m_Buttons.push_back(b1);

	ButtonText* b2 = new ButtonText(L"Quit", { -30.f, 40.f });
	Add(b2);
	m_Buttons.push_back(b2);


	m_Buttons[index]->SetSelected(true);
}

void MenuScene::Update()
{
	Scene::Update();

	App::DrawText(L"Geometry Runner :3", gce::Vector2f32(SCREEN_WIDTH * 0.4f, SCREEN_HEIGHT * 0.2f), gce::Color::Red);

	if (sr::GetKeyDown(sr::Keyboard::UP_ARROW) || sr::GetKeyDown(sr::Keyboard::Z))
	{
		m_Buttons[index]->SetSelected(false);

		index++;

		if (index > BUTTONS_NB - 1)
			index = 0;

		m_Buttons[index]->SetSelected(true);
	}
	else if (sr::GetKeyDown(sr::Keyboard::DOWN_ARROW) || sr::GetKeyDown(sr::Keyboard::S))
	{
		m_Buttons[index]->SetSelected(false);

		index--;

		if (index < 0)
			index = BUTTONS_NB - 1;

		m_Buttons[index]->SetSelected(true);
	}

	if (sr::GetKeyDown(sr::Keyboard::ENTER))
	{
		m_Buttons[index]->OnTrigger();
	}
}
