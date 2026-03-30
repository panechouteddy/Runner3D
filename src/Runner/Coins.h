#pragma once
#include "Entity.h"

enum class CoinConfig
{
	NONE,
	SINGLE,
	STRAIGHT,
	HORIZONTAL,
	Count
};

class Coins : public Entity
{
	int m_value;
public:
	Coins();
	void OnCollision(Entity* pOther) override;
	void Start() override;
	void Update() override;
};

