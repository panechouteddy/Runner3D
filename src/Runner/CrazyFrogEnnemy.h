#pragma once
#include "Entity.h"
class Character;
class CrazyFrogEnnemy : public Entity
{
	Character* m_pPlayer;
	bool m_IsMoving;
	float m_MoveCD;
	float m_jumpCD;
	float m_Speed = 30.f;
	bool m_IsJumping;
	int randomHeight;
public:
	CrazyFrogEnnemy();
	void Start() override;
	void Update() override;
	void OnCollision(Entity* pOther) override;
	void UpdateTime();
	void Move();
	void UpdateJump();
	bool CanMove();
};

