#pragma once
#include "lib/Geometries/Geometries.h"


class Entity
{
protected:
	sr::Geometry* m_geo;

public:
	virtual void Init() = 0;

	virtual void Update(float deltaTime) = 0;

	sr::Geometry* GetGeo() { return m_geo; }
};

