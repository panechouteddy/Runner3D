#pragma once
#include "Entity.h"

class Floor : public Entity
{
public:
	Floor();
	~Floor() = default;

	void Start() override;
	void Update() override;

	void OnCollision(Entity* pOther) override;
};

