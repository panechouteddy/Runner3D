#include "pch.h"
#include "StaticEnnemi.h"
#include "Ressources.h"
#include "App.h"
#include "RunnerScene.h"
#include "SceneManager.h"
#include "PowerUp.h"

StaticEnnemy::StaticEnnemy() : Entity("Static_Ennemi", new sr::Cube)
{
	m_Tag = Tag::TEnnemy;
}

void StaticEnnemy::Start()
{
	SetCollider(true);
	SetColor({ 1.0f,0.5f,0.f });
	SetScale({ 2 ,4, 2 });
	m_IsShooting = false;
	m_ShootCD = DEFAULTCD -2;
	m_Size = 0.0f;
	m_Height = 0.0f;
	m_randomSpeed = std::rand() % 4 + 1;
}

void StaticEnnemy::OnCollision(Entity* pOther)
{
	if (m_IsShooting == false)
	{
		return;
	}
	gce::Vector3f32 otherPos = pOther->GetPosition();

	if (pOther->GetTag() == Tag::TPlayer)
	{

		if (auto pPlayer = dynamic_cast<Character*>(pOther))
		{
			if (m_CollidingFace == Face::Front)
			{
				if (pPlayer->m_Shielded == true)
				{
					pPlayer->RemovePowerUp((int)PowerBall::SHIELD);
					SetCollider(false);
					return;
				}

				pPlayer->Lose();
			}
		}
	}

}




void StaticEnnemy::UpdateSize()
{
	gce::Vector3f32 pos = GetPosition();

	if (m_IsShooting == false)
	{
		m_Size = (DEFAULTCD - m_ShootCD) * 3;

		SetScale({ 2.0f + m_Size , 4.0f, 2.0f + m_Size });
		SetPosition({ pos.x, (Floor_Height + GetScale().y) * 0.5f - GetScale().y, pos.z});

		m_Height = 0.0f;
		if (m_ShootCD <= 0)
		{
			m_IsShooting = true;
			m_ShootCD = DEFAULTCD;
		}
	}
}

void StaticEnnemy::Shoot()
{
	if (m_IsShooting == true)
	{
		gce::Vector3f32 pos = GetPosition();
		m_Height = (DEFAULTCD - m_ShootCD) * 20;
		
		if (GetScale().y <= 40)
		{
			SetScale({ 2.0f + m_Size , m_Height * m_randomSpeed +2, 2.0f + m_Size });
			SetPosition({ pos.x, (Floor_Height + GetScale().y) * 0.5f, pos.z });
		}
		if (m_ShootCD <= 0)
		{
			m_IsShooting = false;
			m_ShootCD = DEFAULTCD;
		}
	}

}

void StaticEnnemy::Update()
{
	m_ShootCD -= App::GetDeltaTime();
	
	UpdateSize();
	Shoot();
}
