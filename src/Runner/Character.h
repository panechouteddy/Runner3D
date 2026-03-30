#pragma once
#include "Entity.h"
#include "Controller.h"

constexpr float DEFAULT_SPEED = 30.f;
constexpr float DEFAULT_LATERAL_SPEED = 40.f;
constexpr float STRENGTH = 0.01f;
constexpr int DEFAULT_JUMPS_AMOUNT = 1;

class PowerUp;

class Character  : public Entity
{
	int m_CharacterStates;
	float m_Strength;
	bool m_Gravity;
	float m_Speed = DEFAULT_SPEED;
	float m_Lateral_Speed = DEFAULT_LATERAL_SPEED;
	bool m_HasLost = false;

	bool m_InvertColor = false;

	int m_JumpsAmount = DEFAULT_JUMPS_AMOUNT;

	std::vector<PowerUp*> m_ActivePowerUps;
public:
	int m_SpeedVariable;
	bool m_Shielded = false;
	bool m_CanDoubleJump = false;
	int m_JumpsBoost = 1;

	enum  States
	{
		IDLE,
		JUMP,
		FALL,
	};
	Character();

	void Start() override;
	void Update() override;
	void OnCollision(Entity* pOther) override;
	void HandleState();
	void UpdateStates();
	void Jump();
	void UpdatePowerUpStatus();
	void AddPowerUp(PowerUp* p);
	void RemovePowerUp(int ID);

	//Get
	float GetSpeed() { return m_Speed; }
	bool HasLost() { return m_HasLost; }
	float GetLateralSpeed() { return m_Lateral_Speed; }
	int GetState() { return m_CharacterStates; }
	int GetJumpsAmount() { return m_JumpsAmount; }

	//Set
	void SetSpeed(float val);
	void SetJumpsAmount(int val) { m_JumpsAmount = val; }
	void Lose() { m_HasLost = true, m_Speed = 0.f; m_Lateral_Speed = 0.f; }
	void SetStrength(float val) { m_Strength = val; }
	void SetState(int state) { m_CharacterStates = state; }
	void SetGravity(bool state) { m_Gravity = state; }

	void Move(int dir);
	void AddSpeed(float val);

	void HandleFalling();
};

