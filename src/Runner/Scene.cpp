#include "pch.h"
#include "Scene.h"
#include "SceneManager.h"
#include "App.h"
#include "Entity.h"
#include <lib/Geometries/Geometry.h>
#include "RunnerCamera.h"
#include "RunnerScene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Clear();
}

void Scene::Clear()
{
	m_pEntititesToAdd.clear();

	for (Entity* e : m_pEntities)
	{
		delete e;
	}

	m_pEntities.clear();

	for (sr::Text* t : m_pTextes)
	{
		delete t;
	}

	m_pTextes.clear();

	quit = false;
}

void Scene::Add(Entity* entity)
{
	m_pEntities.push_back(entity);
	entity->Start(); 
}

void Scene::ToAdd(Entity* entity)
{
	m_pEntititesToAdd.push_back(entity);
}

void Scene::DrawText(std::wstring txt, gce::Vector2f32 pos, gce::Color color)
{
	sr::Text* pText = new sr::Text(txt);

	pText->SetText(txt);
	pText->SetPosition(pos);
	pText->SetColor(color);

	m_pTextes.push_back(pText);
}

void Scene::Draw()
{
	sr::Window* win = App::GetWindow();

	win->Begin(*App::GetRunnerCamera()->GetSRCamera());

	for (Entity* e : m_pEntities)
	{
		if (e->IsVisible() == false)
			continue;

		win->Draw(*e->GetGeo());
	}

	for (auto it = m_pTextes.begin(); it != m_pTextes.end(); ++it)
	{
		win->DrawText(**it);
	}

	win->End();
	win->Display();

	for (auto it = m_pTextes.begin(); it != m_pTextes.end();)
	{
		delete* it;

		it = m_pTextes.erase(it);
	}
}

void Scene::PauseKeyManager()
{
	if (sr::GetKeyDown(sr::Keyboard::ESCAPE))
	{
		isPaused = !isPaused;
	}

	if (isPaused)
	{
		DrawText(L"Continue = Echap", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f - 150 }, gce::Color::Blue);
		DrawText(L"Retry = R", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f - 50 }, gce::Color::Green);
		DrawText(L"Quit = BackSpace (Retour)", { (float)SCREEN_WIDTH * 0.4f,  (float)SCREEN_HEIGHT * 0.5f + 50 }, gce::Color::Red);

		if (sr::GetKeyDown(sr::Keyboard::R))
		{
			isPaused = false;
			App::Get()->GetSceneManager()->ResetCurrentScene();
		}
		else if (sr::GetKeyDown(sr::Keyboard::BACKSPACE))
		{
			isPaused = false;
			quit = true;
		}
	}
}

void Scene::Update()
{
	std::vector<Entity*> entitiesWithCollider;

	gce::Vector3f32 camPos = App::GetRunnerCamera()->GetPosition();

	for (Entity* e : m_pEntities)
	{
		if (e->HasCollider())
		{
			gce::Vector3f32 ePos = e->GetPosition();

			float zDist = std::abs(camPos.z - ePos.z);

			if (zDist < Tile_Size * 2.f) // Don't Collide Entities if they're too far from the camera (linked to the player).
			{
				entitiesWithCollider.push_back(e);
			}
		}
	}

	for (auto it1 = entitiesWithCollider.begin(); it1 != entitiesWithCollider.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != entitiesWithCollider.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			if (entity->IsColliding(otherEntity))
			{
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
			}
		}
	}

	entitiesWithCollider.clear();

	for (Entity* e : m_pEntities)
	{
		if (e->m_ToDestroy == true && e->m_LateDestroy == false)
			continue;

		e->Update();
	}

	if (fpsTimer <= 0.f)
	{
		fpsTimer = 1.f;
		fps = (int)(1.f / App::GetDeltaTime());
	}
	else
	{
		fpsTimer -= App::GetDeltaTime();
	}

	DrawText(L"FPS : " + std::to_wstring(fps), { SCREEN_WIDTH * 0.85f, 0.f }, gce::Color::Black);
}

void Scene::UpdateEntitityTabs()
{
	for (auto it = m_pEntities.begin(); it != m_pEntities.end();)
	{
		if ((*it)->m_ToDestroy == true && (*it)->m_LateDestroy == false)
		{
			delete* it;

			it = m_pEntities.erase(it);
		}
		else
		{
			(*it)->SetFace(Face::NONE);

			++it;
		}
	}

	for (Entity* e : m_pEntititesToAdd)
	{
		Add(e);
	}

	m_pEntititesToAdd.clear();
}
