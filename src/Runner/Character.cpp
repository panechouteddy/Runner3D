#include "pch.h"
#include "Character.h"
#include "App.h"
#include "Ressources.h"
#include "RunnerScene.h"
#include "PowerUp.h"

constexpr int YPOSITION = 10;
constexpr int ZPOSITION = -35;
constexpr int SCALEWIDTH = 5;
constexpr float JUMPSPEED = 75.f;

Character::Character() : Entity("Character", new sr::Sphere)
{
	m_Tag = Tag::TPlayer;
}

void Character::Start()
{
	SetCollider(true);
	SetColor({0, 1, 0});
	SetScale({ SCALEWIDTH,SCALEWIDTH,SCALEWIDTH });
	m_Strength = STRENGTH;
	m_CharacterStates = IDLE;
	SetPosition({ 0.f,YPOSITION, ZPOSITION });
	m_Gravity = true;

	m_Shielded = false;
	m_CanDoubleJump = false;
	m_SpeedVariable = 1;
}

void Character::OnCollision(Entity* pOther)
{
	gce::Vector3f32 myPos = GetPosition();
	gce::Vector3f32 otherPos = pOther->GetPosition();
	int tag = pOther->GetTag();

	if (tag == TFloor || tag == TWall || tag == TEnnemy)
	{
		if (m_CollidingFace == Face::Down)
		{
			SetPosition({ myPos.x,  otherPos.y + (GetScale().y + pOther->GetScale().y) * 0.5f, myPos.z });

			if (m_CharacterStates != JUMP)
			{
				if (m_CharacterStates != Character::JUMP)
				{
					int boost = 1;

					if (m_CanDoubleJump)
						boost = 2;

					SetJumpsAmount(DEFAULT_JUMPS_AMOUNT * boost);
				}

				m_Gravity = false;
				m_CharacterStates = IDLE;
				m_Strength = STRENGTH;
			}
		}

		if (m_CollidingFace == Face::Back)
		{
			SetPosition({ myPos.x, myPos.y, otherPos.z - (GetScale().z + pOther->GetScale().z) * 0.5f - 0.1f });
		}

		if (m_CollidingFace == Face::Right)
			SetPosition({ otherPos.x - (GetScale().x + pOther->GetScale().x) * 0.5f, myPos.y, myPos.z });

		if (m_CollidingFace == Face::Left)
			SetPosition({ otherPos.x + (GetScale().x + pOther->GetScale().x) * 0.5f, myPos.y, myPos.z });
	}
}

void Character::Update()
{
	UpdatePowerUpStatus();
	UpdateStates();
	HandleState();
	HandleFalling();
	AddSpeed(App::GetDeltaTime() * 0.5f);

	m_Gravity = true;

	if (m_HasLost)
	{
		App::DrawText(L"You Lost ! :3", { SCREEN_WIDTH * 0.42f, SCREEN_HEIGHT * 0.5f }, gce::Color(255, 100, 255, 255));
	}
}

void Character::HandleState()
{
	if (m_IsVisible == false)
		return;

	float DT = App::GetDeltaTime();

	gce::Vector3f32 PlayerMove = { 0.f, 0.f, 0.f };

	if (m_HasLost == false)
	{
		PlayerMove.z += DT * m_Speed;

		if (m_CharacterStates == JUMP)
		{
			PlayerMove.y += DT * JUMPSPEED;
		}
	}

	if (m_CharacterStates != IDLE)
	{
		PlayerMove.y -= DT * m_Strength;

		if (m_Strength > 500.f)
			m_Strength = 500.f;
		else
			m_Strength += DT * 100.f;
	}

	Translate(PlayerMove);
}

void Character::UpdateStates()
{
	gce::Vector3f32 PlayerPosition = GetPosition();

	if (m_Gravity == true)
	{
		if (m_CharacterStates == IDLE)
		{
			m_CharacterStates = FALL;
		}
	}

	if (m_CharacterStates == JUMP)
	{
		if (m_Strength >= JUMPSPEED)
		{
			m_CharacterStates = FALL;
			m_Strength = STRENGTH;
		}
		else
		{
			m_Gravity = false;
		}
	}
}

void Character::Jump()
{
	if (m_JumpsAmount > 0)
	{
		m_Strength = STRENGTH;
		m_CharacterStates = JUMP;
		m_JumpsAmount--;
	}
}

void Character::UpdatePowerUpStatus()
{
	if (m_ActivePowerUps.empty())
	{
		SetColor({ 0, 1, 0 });
		return;
	}

	auto it = m_ActivePowerUps.rbegin();

	SetColor((*it)->GetColor());

	for (auto it = m_ActivePowerUps.begin(); it != m_ActivePowerUps.end(); ++it)
	{
		std::wstring time = std::to_wstring((int)(*it)->GetTime() + 1);

		if ((*it)->m_ID == (int)PowerBall::SHIELD)
		{
			App::DrawText(L" Shield : " + time + L"s", { 0.f, 300.f }, gce::Color::Blue);
		}
		else if ((*it)->m_ID == (int)PowerBall::DOUBLEJUMP)
		{
			App::DrawText(L" Double Jump : " + time + L"s", { 0.f, 400.f }, gce::Color(255, 160, 255, 255));
		}
		else if ((*it)->m_ID == (int)PowerBall::SPEED)
		{
			App::DrawText(L" Lateral Boost : " + time + L"s", { 0.f, 500.f }, gce::Color(255, 100, 0, 255));
		}
	}
}

void Character::AddPowerUp(PowerUp* p)
{
	for (auto it = m_ActivePowerUps.begin(); it != m_ActivePowerUps.end(); ++it)
	{
		if ((*it)->m_ID == p->m_ID)
		{
			(*it)->m_LateDestroy = false;
			it = m_ActivePowerUps.erase(it);
			break;
		}
	}

	m_ActivePowerUps.push_back(p);
}

void Character::RemovePowerUp(int ID)
{
	for (auto it = m_ActivePowerUps.begin(); it != m_ActivePowerUps.end(); ++it)
	{
		if ((*it)->m_ID == ID)
		{
			(*it)->LosePowerUp(); 
			it = m_ActivePowerUps.erase(it);

			break;
		}
	}
}

void Character::SetSpeed(float val)
{
	m_Speed = val;

	float ratio = DEFAULT_LATERAL_SPEED / DEFAULT_SPEED;

	m_Lateral_Speed = m_Speed * ratio;
}

void Character::Move(int dir)
{
	Translate({ dir * m_Lateral_Speed * m_SpeedVariable * App::GetDeltaTime(), 0.f, 0.f });
}

void Character::AddSpeed(float val)
{
	if (m_HasLost)
		return;
	m_Speed += val;

	float ratio = DEFAULT_LATERAL_SPEED / DEFAULT_SPEED;

	m_Lateral_Speed = m_Speed * ratio;
}

void Character::HandleFalling()
{
	if (GetPosition().y < - 10.f)
		Lose();

	if (GetPosition().y < -300.f)
	{
		SetVisibility(false);
	}
}

