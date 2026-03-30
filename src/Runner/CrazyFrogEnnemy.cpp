#include "pch.h"
#include "CrazyFrogEnnemy.h"
#include "Ressources.h"
#include "App.h"
#include "RunnerScene.h"
#include "SceneManager.h"
#include "PowerUp.h"

CrazyFrogEnnemy::CrazyFrogEnnemy() : Entity("CrazyFrogEnnemy", new sr::Cube)
{
	m_Tag = Tag::TEnnemy;
}

void CrazyFrogEnnemy::Start()
{
	m_pPlayer = App::Get()->GetSceneManager()->GetScene<RunnerScene>()->GetPlayer();
	m_Speed = m_pPlayer->GetSpeed();
	SetCollider(true);
	SetColor({ 1.0f,0.5f,0.f });
	SetScale({ 4 ,4, 4 });
	m_IsJumping = true;
	m_IsMoving = false;
	m_MoveCD = DEFAULTCD - 3;
	randomHeight = std::rand() % 3 + 3;
}

void CrazyFrogEnnemy::Update()
{
	if (CanMove())
	{
		Move();
		UpdateJump();
	}
	else
	{
		UpdateTime();
	}
}

void CrazyFrogEnnemy::OnCollision(Entity* pOther)
{
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
void CrazyFrogEnnemy::UpdateTime()
{
	float m_Size = (DEFAULTCD - m_MoveCD) * 3;

	SetScale({ 2.0f + m_Size , 2.0f + m_Size, 2.0f + m_Size });
	if (m_MoveCD <= 0)
	{
		m_IsMoving = true;
	}
	else
	{
		m_MoveCD -= App::GetDeltaTime();
	}
}
void CrazyFrogEnnemy::Move()
{
	float DT = App::GetDeltaTime();

	gce::Vector3f32 Move = { 0,0,0 };
	Move.z -= DT * m_Speed;
	if (m_IsJumping)
	{
		Move.y += DT * m_Speed;
	}
	else
	{
		Move.y -= DT * m_Speed;
	}
	Translate(Move);

}

void CrazyFrogEnnemy::UpdateJump()
{
	gce::Vector3f32 RePosition;
	if (GetPosition().y < 15)
	{
		SetPosition({ GetPosition().x,15,GetPosition().z });
		m_IsJumping = true;
		return;
	}
	if (GetPosition().y > 30)
	{
		SetPosition({ GetPosition().x,30 ,GetPosition().z });
		m_IsJumping = false;
		return;
	}
}

bool CrazyFrogEnnemy::CanMove()
{
	if (m_IsMoving == false)
	{
		return false;
	}
	float difZ = GetPosition().z - m_pPlayer->GetPosition().z;
	if ( difZ <= Tile_Size * randomHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}
