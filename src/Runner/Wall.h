#pragma once
#include "Entity.h"

enum class WallConfig
{
	NONE,
	LOW,
	HIGH,
	UNDER,
	UNDEROVER,
	Count
};


class Wall : public Entity
{
public:
	Wall();
	void Start() override;
	void Update() override;

	void OnCollision(Entity* pOther) override;
};

