#include "pch.h"
#include "Coins.h"
#include "App.h"
#include "RunnerScene.h"
#include "SceneManager.h"

constexpr int SCALEWIDTH = 1;
constexpr int SCALEHEIGHT = 5;
constexpr int ROTATIONX = 90;

Coins::Coins() : Entity("Coin", new sr::Cylinder())
{
	m_Tag = Tag::TCoin;
}

void Coins::OnCollision(Entity* pOther)
{
	if (pOther->GetTag() == TPlayer)
	{
		if (m_IsVisible)
		{
			App::Get()->GetSceneManager()->GetScene<RunnerScene>()->AddCoinScore();
			m_IsVisible = false;
		}
	}
}

void Coins::Start()
{
	SetCollider(true);
	SetColor({ 1.f, 1.f, 0.f });
	SetScale({ SCALEHEIGHT,SCALEWIDTH,SCALEHEIGHT });
	SetRotation({ ROTATIONX,0,0 });
}

void Coins::Update()
{
	Rotate({ 0, 5.f * App::GetDeltaTime(), 0 });
}
