#include "pch.h"
#include "MoveEnnemy.h"
#include "Ressources.h"
#include "App.h"
#include "RunnerScene.h"
#include "SceneManager.h"
#include "PowerUp.h"

MoveEnnemy::MoveEnnemy() : Entity("moveEnnemy",new sr::Cube)
{
	m_Tag = Tag::TEnnemy;
	m_RandomHeight = rand() % 3 + 3;
	m_RandomSize = 1 + rand() % 2;
}

void MoveEnnemy::Start()
{
	m_pPlayer = App::Get()->GetSceneManager()->GetScene<RunnerScene>()->GetPlayer();
	m_Speed = m_pPlayer->GetSpeed();

	SetCollider(true);
	SetColor({ 1.0f,0.5f,0.f });
	m_IsMoving= false;
	m_MoveCD = DEFAULTCD - 1;
}

void MoveEnnemy::Update()
{
	if (CanMove())
	{
		Move();
	}
	else
	{
		UpdateTime();
	}

}

void MoveEnnemy::OnCollision(Entity* pOther)
{
	gce::Vector3f32 otherPos = pOther->GetPosition();

	if (pOther->GetTag() == Tag::TPlayer)
	{
		if (auto pPlayer = dynamic_cast<Character*>(pOther))
		{
			if(m_CollidingFace == Face::Front)
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

void MoveEnnemy::UpdateTime()
{
	float m_Size = (DEFAULTCD - m_MoveCD) * 3;

	if (m_IsMoving == false)
	{
		gce::Vector3f32 pos = GetPosition();

		SetScale({ 3.0f + m_Size , (7.f + m_Size) * (float)m_RandomSize, 3.0f + m_Size });
		SetPosition({ pos.x, (Floor_Height + GetScale().y) * 0.5f, pos.z});
	}

	if (m_MoveCD <= 0)
	{
		m_IsMoving= true;
	}
	else
	{
		m_MoveCD -= App::GetDeltaTime();
	}
}
void MoveEnnemy::Move()
{
	float DT = App::GetDeltaTime();

	gce::Vector3f32 Move = { 0,0,0};
	Move.z -= DT * m_Speed;
	Translate(Move);
}
bool MoveEnnemy::CanMove()
{
	if (m_IsMoving == false)
	{
		return false;
	}
	float difZ = GetPosition().z - m_pPlayer->GetPosition().z;
	if (difZ <= Tile_Size * m_RandomHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
 }