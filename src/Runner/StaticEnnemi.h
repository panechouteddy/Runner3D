#pragma once
#include "Entity.h"

class StaticEnnemy : public Entity
{
	bool m_IsShooting;
	float m_ShootCD;
	float m_Size;
	float m_Height;
	float m_randomSpeed;
public:
	StaticEnnemy();
	void Start() override;
	void Update() override;
	void OnCollision(Entity* pOther) override;
	void UpdateSize();
	void Shoot();
};

