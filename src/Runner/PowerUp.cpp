#include "pch.h"
#include "PowerUp.h"
#include "Ressources.h"
#include "App.h"
#include "Ressources.h"
#include "RunnerScene.h"
#include "SceneManager.h"

constexpr float DEFAULT_DURATION = 10.f;

constexpr float SHIELD_TIME = 10.f;
constexpr float DOUBLEJUMP_TIME = 5.f;
constexpr float LATERALSPEED_TIME = 7.f;

PowerUp::PowerUp(const char* name) :Entity(name, new sr::Sphere)
{
	m_Color = { 1.f, 1.f, 1.f };
	m_LateDestroy = true;

	m_pPlayer = App::Get()->GetSceneManager()->GetScene<RunnerScene>()->GetPlayer();
	m_Timer = DEFAULT_DURATION;
	m_Tag = TPowerUp;
	m_Activated = false;
}

void PowerUp::Update()
{
	if (m_Activated == true)
	{
		if(m_Timer >= 0.f)
		{
			m_Timer -= App::GetDeltaTime();

			OnActivation();
		}
		else
		{
			LosePowerUp();
			m_pPlayer->RemovePowerUp(m_ID);
		}
	}
}

void PowerUp::OnCollision(Entity* pOther)
{
	if (m_IsVisible == false)
		return;

	if (pOther->GetTag() == TPlayer)
	{
		m_pPlayer->AddPowerUp(this);

		m_IsVisible = false;
		m_Activated = true;
		m_Timer = DEFAULT_DURATION;
	}
}

void PowerUp::LosePowerUp()
{
	OnDesactivation();
	m_LateDestroy = false;
	m_Activated = false;
	m_Timer = 0.f;
	m_IsTrigger = false;
}

void ShieldBall::Start()
{
	m_Color = { 0.f, 0.f, 1.f };
	m_Timer = SHIELD_TIME;

	SetCollider(true);
	SetColor(m_Color);
	SetScale({ 3 ,3, 3 });
}

void ShieldBall::Update()
{
	PowerUp::Update();
}

void ShieldBall::OnActivation()
{
	if (m_IsTrigger == true)
		return;

	m_IsTrigger = true;

	m_pPlayer->m_Shielded = true;
}

void ShieldBall::OnDesactivation()
{
	m_pPlayer->m_Shielded = false;
}

void DoubleJumpBall::Start()
{
	m_Color = { 1.f, 0.6f, 1.f };
	m_Timer = DOUBLEJUMP_TIME;

	SetCollider(true);
	SetColor(m_Color);
	SetScale({ 3 ,3, 3 });
}

void DoubleJumpBall::Update()
{
	PowerUp::Update();
}

void DoubleJumpBall::OnActivation()
{
	m_pPlayer->m_CanDoubleJump = true;
}

void DoubleJumpBall::OnDesactivation()
{
	m_pPlayer->m_CanDoubleJump = false;
}

void SpeedBall::Start()
{
	m_Color = { 1.f, 0.33f, 0.f };
	m_Timer = LATERALSPEED_TIME;

	SetCollider(true);
	SetColor(m_Color);
	SetScale({ 3 ,3, 3 });
}

void SpeedBall::Update()
{
	PowerUp::Update();
}

void SpeedBall::OnActivation()
{
	m_pPlayer->m_SpeedVariable = 1.75f;
}

void SpeedBall::OnDesactivation()
{
	m_pPlayer->m_SpeedVariable = 1;
}
