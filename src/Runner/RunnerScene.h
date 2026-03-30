#pragma once
#include "Scene.h"
#include "GCSR.h"
#include "RunnerCamera.h"
#include "TileGenerator.h"
#include "Character.h"
#include "Coins.h"
#include "Ressources.h"

enum Tag
{
	TPlayer,
	TFloor,
	TCoin,
	TPowerUp,
	TWall,
	TEnnemy,
	Count
};

class MoveEnnemy;
class StaticEnnemy;

class Controller;

class RandomConfigGenerator;
class Entity;
class RunnerScene : public Scene
{
public:

	static constexpr int TAG_COUNT = static_cast<int>(Count);

	bool m_FpsMod = false;

private:
	int m_Interactions[TAG_COUNT][TAG_COUNT];
	int m_Coins_Number;
	long int m_Score = 0;
	float m_Progress_Score = 0.f;

	Controller* m_pController = nullptr;
	Character* m_pCharacter = nullptr;

	TileGenerator m_TileGenerator;
	RandomConfigGenerator* m_RCG = nullptr; //Random Config Generator

	StaticEnnemy* m_pStaticEnnemi = nullptr;
	MoveEnnemy* m_pMoveEnnemy = nullptr;
public:
	void Init() override;
	void Update() override;
	void Clear() override;
	void AddCoinScore() { m_Coins_Number++; }

	void InitCamSettings();
	void InitTransitions();

	void HandleScore();

	void UIManager();

	void SwapFPSMod() { m_FpsMod = !m_FpsMod; }
	void FPSModManager();

	void SetTransitionBetween(int tag1, int tag2, bool state) override;
	bool IsAllowedToCollide(int tag1, int tag2) override;
	Character* GetPlayer() { return m_pCharacter; }
};

