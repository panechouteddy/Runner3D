#pragma once
#include "lib/Geometries/Geometries.h"

class Collider
{
public:

	float mRayon = 0;
	int mType;
	bool mRebound = false;
	
	sr::Geometry* m_pGeo;

	gce::Vector3f32* m_pVelocity;
	gce::Vector3f32 mForce = { 0, 0, 0 };

	virtual void OnCollision() = 0;
};

