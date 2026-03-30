#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	m_pCurrentScene = nullptr;

	for (auto it = m_pScenes.begin(); it != m_pScenes.end(); ++it)
	{
		delete it->second;
	}

	m_pScenes.clear();
}

void SceneManager::AddScene(const char* name, Scene* scene)
{
	m_pScenes[name] = scene;
	m_pCurrentScene = scene;
}

void SceneManager::ChangeScene(const char* name)
{
	Scene* newScene = m_pScenes[name];

	if (newScene == nullptr)
	{
		std::cerr << "The scene : " << name << ", doesn't exist !\n";
		return;
	}

	if (newScene == m_pCurrentScene)
	{
		std::cerr << "You're already in this scene : " << name << " !\n";
		return;
	}

	m_pCurrentScene->Clear();
	m_pCurrentScene = newScene;
	m_pCurrentScene->Init();
}

void SceneManager::ResetCurrentScene()
{
	m_pCurrentScene->Clear();
	m_pCurrentScene->Init();
}