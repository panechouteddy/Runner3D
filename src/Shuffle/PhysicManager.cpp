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

			gce::Vector3f32 pos1 = collider[i]->m_pGeo->GetPosition();
			gce::Vector3f32 pos2 = collider[j]->m_pGeo->GetPosition();

			gce::Vector3f32 dir = pos2 - pos1;
			float dist = sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y) + (pos1.z - pos2.z) * (pos1.z - pos2.z));
			float minDist = collider[i]->mRayon + collider[j]->mRayon;

			if (dist <= collider[i]->mRayon + collider[j]->mRayon)
			{
				collider[i]->OnCollision();
				collider[j]->OnCollision();

				float overlap = 0.5f * (minDist - dist);
				dir = dir / dist;

				pos1 -= dir * overlap;
				pos2 += dir * overlap;

				collider[i]->m_pGeo->SetPosition(pos1);
				collider[j]->m_pGeo->SetPosition(pos2);

				//rebond
				if (collider[i]->mRebound || collider[j]->mRebound)
				{
					float restitution = 0.8f;

					gce::Vector3f32 v1 = *collider[i]->m_pVelocity;
					gce::Vector3f32 v2 = *collider[j]->m_pVelocity;

					gce::Vector3f32 rv = v2 - v1;

					float temp = rv.x * dir.x + rv.y * dir.y + rv.z * dir.z;

					float cImpulse = -(1 + restitution) * temp / 2.0f;
					gce::Vector3f32 impulse = dir * cImpulse;

					if (collider[i]->mRebound)
						*collider[i]->m_pVelocity -= impulse;

					if (collider[j]->mRebound)
						*collider[j]->m_pVelocity -= impulse;
				}
			}
		}
	}
}
