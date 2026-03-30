#include "pch.h"
#include "Floor.h"
#include "App.h"
#include "Ressources.h"
#include "RunnerScene.h"

Floor::Floor() : Entity("Floor", new sr::Cube())
{
	m_Tag = Tag::TFloor;

	SetColor({ 0.f, 1.f, 1.f });
}

void Floor::Start()
{
	SetCollider(true);
}

void Floor::Update()
{
}

void Floor::OnCollision(Entity* pOther)
{
}
