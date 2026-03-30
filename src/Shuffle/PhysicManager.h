#pragma once
#include "lib/Geometries/Geometries.h"

class Collider;

class PhysicManager
{
public:

	void CheckCollision(std::vector<Collider*> entity);
};

