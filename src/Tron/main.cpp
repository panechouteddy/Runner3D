#include "pch.h"
#include "main.h"

#include <iostream>
#include <chrono>

#include "GameManager.h"
#include "TronManager.h"


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    srand(time(NULL));

    auto lastTime = std::chrono::high_resolution_clock::now();

    //Window creation
    sr::Window window(L"Test", 1920 / 2, 1080 / 2);

    //Camera creation
    sr::Camera camera(sr::CameraType::PERSPECTIVE);
    camera.SetPosition({ 0.0f, 50.0f, 0.0f });
    camera.SetRotation({ 90.0f, 0.0f, 0.0f });
    camera.SetFOV(gce::PI / 4.0f);
    camera.SetFarPlane(500.0f);
    camera.SetNearPlane(0.001f);

    TronManager gameManager;
    gameManager.Init();

    //Rendering Loop
    while (window.IsOpen())
    {
        //deltaTime
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> delta = currentTime - lastTime;
        float deltaTime = delta.count();

        lastTime = currentTime;

        window.Begin(camera);

        gameManager.Draw(window);

        window.End();

        window.Display();

        gameManager.Update(deltaTime);

    }
	gameManager.CleanAll();

    return 0;
}