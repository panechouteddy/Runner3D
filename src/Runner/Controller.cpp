#include "pch.h"
#include "Controller.h"
#include "GCSR.h"
#include "Character.h"
#include "Ressources.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RunnerScene.h"

Controller::Controller()
{
	Init();
}

void Controller::Init()
{
	m_pOwner = App::Get()->GetSceneManager()->GetScene<RunnerScene>()->GetPlayer();
}

void Controller::Update()
{
	if (m_pOwner == nullptr)
		return;

	HandleCamView();

	if (m_pOwner->HasLost())
		return;

	HandleMoving();
	HandleJump();
	HandleFastFall();
}

void Controller::HandleMoving()
{
	int dir = sr::GetKey(sr::Keyboard::D) - sr::GetKey(sr::Keyboard::Q);

	m_pOwner->Move(dir);
}

void Controller::HandleJump()
{
	if (sr::GetKeyDown(sr::Keyboard::SPACE))
	{
		if (m_pOwner->GetState() == Character::IDLE || m_pOwner->m_CanDoubleJump)
		{
			m_pOwner->Jump();
			return;
		}
	}
}

void Controller::HandleFastFall()
{
	if (sr::GetKeyDown(sr::Keyboard::S))
	{
		m_pOwner->SetState(Character::FALL);
		m_pOwner->SetStrength(100.f);
	}
}

void Controller::HandleCamView()
{
	if (sr::GetButtonDown(sr::Mouse::RIGHT))
	{
		App::Get()->GetSceneManager()->GetScene<RunnerScene>()->SwapFPSMod();
	}
}
