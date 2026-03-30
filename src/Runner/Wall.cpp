#include "pch.h"
#include "Wall.h"
#include "Ressources.h"
#include "RunnerScene.h"
#include "App.h"
#include "SceneManager.h"
#include "PowerUp.h"

Wall::Wall() : Entity("Wall", new sr::Cube())
{
	m_Tag = Tag::TWall;
}

void Wall::Start()
{
	SetColor({ 1.f, 0.f, 0.f });
	SetCollider(true);
}

void Wall::Update()
{

}
void Wall::OnCollision(Entity* pOther)
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