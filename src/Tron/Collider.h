#pragma once
#include "lib/Geometries/Geometries.h"

class Collider
{
public:
	int m_Type = 0; //0 = Player, 1 = Trail

	float mRayon = 0;
	gce::Vector3f32 m_halfSize = { 0,0,0 };

	bool mRebound = false;
	
	
	sr::Geometry* m_pGeo;

	gce::Vector3f32* m_pVelocity;
	gce::Vector3f32 mForce = { 0, 0, 0 };

	virtual void OnCollision() = 0;
};

