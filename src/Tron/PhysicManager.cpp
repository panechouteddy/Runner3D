#include "pch.h"
#include "PhysicManager.h"

#include "Collider.h"

void PhysicManager::CheckCollision(std::vector<Collider*> collider)
{
	for (int i = 0; i < collider.size(); i++)
	{
		for (int j = i + 1; j < collider.size(); j++)
		{
			if (collider[i] == collider[j])
				continue;

			if (collider[i]->m_Type == 0 && collider[j]->m_Type == 1) // Player - Trail
			{
				if (CollisionCircleRect(collider[i], collider[j]) == true)
				{
					collider[i]->OnCollision();
					collider[j]->OnCollision();
				}
				continue;
			}
			else if (collider[i]->m_Type == 1 && collider[j]->m_Type == 0) // Trail - Player
			{
				if (CollisionCircleRect(collider[j], collider[i]) == true)
				{
					collider[i]->OnCollision();
					collider[j]->OnCollision();
				}
				continue;
			}

			gce::Vector3f32 pos1 = collider[i]->m_pGeo->GetPosition();
			gce::Vector3f32 pos2 = collider[j]->m_pGeo->GetPosition();

			gce::Vector3f32 dir = pos2 - pos1;
			float dist = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z));
			float minDist = collider[i]->mRayon + collider[j]->mRayon;

			if (dist <= collider[i]->mRayon + collider[j]->mRayon)
			{
				collider[i]->OnCollision();
				collider[j]->OnCollision();
			}
		}
	}
}

bool PhysicManager::CollisionCircleRect(Collider* circle, Collider* rect)
{
	gce::Vector3f32 posCircle = circle->m_pGeo->GetPosition();
	gce::Vector3f32 posRect = rect->m_pGeo->GetPosition();

	gce::Vector3f32 H = rect->m_halfSize;
	float radius = circle->mRayon;

	float closestX = gce::Clamp(posCircle.x, posRect.x - H.x, posRect.x + H.x);
	float closestZ = gce::Clamp(posCircle.z, posRect.z - H.z, posRect.z + H.z);

	float distX = posCircle.x - closestX;
	float distZ = posCircle.z - closestZ;
	float dist2 = distX * distX + distZ * distZ;

	if (dist2 > radius * radius)
		return false;

	return true;
}
