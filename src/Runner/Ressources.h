#pragma once
#include "GCSR.h"

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;

constexpr float Floor_Height = 15.f;
constexpr float Tile_Size = 30.f;

// Time
constexpr float DEFAULTCD = 3.0f;

namespace TextureName
{
	constexpr const char* Grass = "grass"; 
	constexpr const char* Brick = "brick";
}

namespace SceneName
{
	constexpr const char* Menu = "menu_scene";
	constexpr const char* Runner = "runner_scene";
}

static gce::Vector3f32 ConvertColorToFloat(int r, int g, int b)
{
	return gce::Vector3f32((float)r / 255.f, (float)g / 255.f, (float)b / 255.f);
}

// ALL ENTITIES NAME FOR EDITOR

////// Shorcuts

constexpr const int __ = -1; // Nothing

//Walls
constexpr int WL = 1000; // Low Wall
constexpr int WH = 1001; // High Wall
constexpr int WU = 1002; // Under Wall
constexpr int WO = 1003; // Under Over Wall

//Coins
constexpr int CO = 1004; // One Coin
constexpr int CS = 1005; // Straight Coins
constexpr int CH = 1006; // Horizontal Coins

//Mobs
constexpr int MS = 1007; // Static Mob
constexpr int MM = 1008;// Moving Mob
constexpr int MF = 1009;// Crazy Mob

namespace Editor
{
	namespace Wall
	{
		constexpr int Low = WL; 
		constexpr int High = WH;
		constexpr int Under = WU;
		constexpr int UnderOver = WO;
	}

	namespace Coin
	{
		constexpr int One = CO;
		constexpr int Straight = CS;
		constexpr int Horizontal = CH;
	}

	namespace Mob
	{
		constexpr int Static = MS;
		constexpr int Moving = MM;
		constexpr int CrazyF = MF;
	}
}
