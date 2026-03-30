#pragma once
#include "lib/Geometries/Geometries.h"


class Entity
{
public:
	sr::Geometry* m_geo;

	virtual void Init() = 0;

	virtual void Update(float deltaTime) = 0;
};

