#pragma once
#include "Entity.h"

enum class PowerBall
{
	NONE,
	SHIELD,
	DOUBLEJUMP,
	SPEED,

	Count
};

class Character;
class PowerUp : public Entity
{
protected:
	Character* m_pPlayer = nullptr;
	float m_Timer;
	bool m_IsTrigger = false;
	bool m_Activated = false;
	gce::Vector3f32 m_Color;
public:
	int m_ID = NONE;

	PowerUp(const char* name);

	gce::Vector3f32 GetColor() { return m_Color; }

	float GetTime() { return m_Timer; }

	bool IsActivated() { return m_Activated; }

	void Update() override;
	virtual void OnCollision(Entity* pOther);
	virtual void OnActivation() = 0;
	virtual void OnDesactivation() = 0;
	void LosePowerUp();
};

class ShieldBall : public PowerUp
{
public:
	ShieldBall() : PowerUp("ShieldBall") { m_ID = (int)PowerBall::SHIELD; }
	void Start() override;
	void Update() override;
	void OnActivation() override;
	void OnDesactivation() override;
};
class DoubleJumpBall : public PowerUp
{
public:
	DoubleJumpBall() : PowerUp("DoubleJumpBall") { m_ID = (int)PowerBall::DOUBLEJUMP; }
	void Start() override ;
	void Update() override;
	void OnActivation() override;
	void OnDesactivation() override;
};
class SpeedBall : public PowerUp
{

public:
	SpeedBall() : PowerUp(" SpeedBall") { m_ID = (int)PowerBall::SPEED; }
	void Start() override ;
	void Update() override;
	void OnActivation() override;
	void OnDesactivation() override;
};