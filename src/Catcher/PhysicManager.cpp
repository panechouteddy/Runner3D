#include "pch.h"
#include "PhysicManager.h"

#include "Collider.h"

void PhysicManager::CheckCollision(std::vector<Collider*> collider)
{
	for (int i = 0; i < collider.size(); i++)
	{
		for (int j = i + 1; j < collider.size() - i; j++)
		{
			if (collider[i] == collider[j])
				continue;

			gce::Vector3f32 pos1 = collider[i]->m_pGeo->GetPosition();
			gce::Vector3f32 pos2 = collider[j]->m_pGeo->GetPosition();

			float dist = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z));

			if (dist <= collider[i]->mRayon + collider[j]->mRayon)
			{
				collider[i]->OnCollision();
				collider[j]->OnCollision();
			}
		}
	}
}
