#include "pch.h"
#include "ButtonText.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"

ButtonText::ButtonText(std::wstring txt, gce::Vector2f32 offsetCenter, const char* sceneToGo) : Entity("Button", new sr::Sphere())
{
	m_Txt = txt;
	m_Pos += offsetCenter;
	m_SceneToGo = sceneToGo;
}

void ButtonText::Start()
{
}

void ButtonText::Update()
{
	App::DrawText(m_Txt, m_Pos, m_Color);

	if (m_Selected == false)
	{
		ResetColor();
		return;
	}

	SetColor(gce::Color::Yellow);
}

void ButtonText::OnTrigger()
{
	if (m_Selected == false)
		return;

	if (sr::GetKeyDown(sr::Keyboard::ENTER))
	{
		if (m_SceneToGo == "")
		{
			App::Get()->running = false;
		}
		else
			App::Get()->GetSceneManager()->ChangeScene(m_SceneToGo);
	}
}
