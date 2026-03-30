#pragma once
#include "GCSR.h"
#include "Ressources.h"

class RunnerCamera;
class SceneManager;

class App
{
	static App* m_Inst;

	sr::Window* m_pWindow = nullptr;

	float dt = 0; // DeltaTime

	SceneManager* m_pSceneManager = nullptr; 
	RunnerCamera* m_pCam = nullptr;
	std::map<const char*, sr::Texture*> m_pTextures;
public:
	bool running = true;
	void Shutdown();
	// Get
	static App* Get();
	static sr::Window* GetWindow() { return Get()->m_pWindow; }
	static RunnerCamera* GetRunnerCamera() { return Get()->m_pCam; }
	static float GetDeltaTime() { return Get()->m_pWindow->GetDeltaTime(); }
	static sr::Texture* GetTexture(const char* name) { return Get()->m_pTextures[name]; }
	static void DrawText(std::wstring txt, gce::Vector2f32 pos, gce::Color color);

	SceneManager* GetSceneManager() { return m_pSceneManager; }

	// Main
	void Init();
	void Run();
};

