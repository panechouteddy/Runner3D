#pragma once
#include "Entity.h"

class Character;
class MoveEnnemy : public Entity
{
	Character* m_pPlayer;
	bool m_IsMoving;
	float m_MoveCD;
	float m_Speed = 30.f;
	int m_RandomHeight;
	int m_RandomSize;
public:
	MoveEnnemy();
	void Start() override;
	void Update() override;

	int GetRandomSize() { return m_RandomSize; }

	void OnCollision(Entity* pOther) override;
	void UpdateTime();
	void Move();
	bool CanMove();
};

