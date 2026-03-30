#pragma once
#include "lib/Geometries/Geometries.h"

class Collider
{
public:
	float mRayon = 0;

	int mType;

	sr::Geometry* m_pGeo;

	virtual void OnCollision() {};
};

