#include "pch.h"
#include "App.h"
#include "Ressources.h"

#include "SceneManager.h"
#include "RunnerScene.h"
#include "MenuScene.h"

#include "RunnerCamera.h"

App* App::m_Inst = nullptr;

void App::Shutdown()
{
    delete m_pSceneManager;
    m_pSceneManager = nullptr;

    delete m_pWindow;
    m_pWindow = nullptr;

    m_pTextures.clear();
}

App* App::Get()
{
    if (m_Inst == nullptr)
    {
        m_Inst = new App();
    }

    return m_Inst;
}

void App::Init()
{
    srand(time(nullptr));

    //Window creation
    m_pWindow = new sr::Window(L"Geometry Runner :3", SCREEN_WIDTH, SCREEN_HEIGHT, sr::Window::FLAG_ENABLE_SHADOWPASS | sr::Window::FLAG_MSAA_X4);
  
    //Camera creation
    m_pCam = new RunnerCamera();
    m_pCam->Init();

    //Scenes
    m_pSceneManager = new SceneManager();
    m_pSceneManager->AddScene(SceneName::Runner, new RunnerScene());
    m_pSceneManager->AddScene(SceneName::Menu, new MenuScene());
}

void App::Run() 
{
    Init();

	Scene* firstScene = m_pSceneManager->GetCurrentScene();

	firstScene->Init();

	while (m_pWindow->IsOpen() && running == true)
	{
        Scene* currentScene = m_pSceneManager->GetCurrentScene();

        if (currentScene != nullptr)
        {
            currentScene->Draw();

            currentScene->Update();

            currentScene->UpdateEntitityTabs();
        }
	}
}

void App::DrawText(std::wstring txt, gce::Vector2f32 pos, gce::Color color)
{
    Get()->GetSceneManager()->GetCurrentScene()->DrawText(txt, pos, color);
}