#include "pch.h"
#include "Entity.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RunnerScene.h"

Entity::~Entity()
{
	/*delete m_pGeo;
	m_pGeo = nullptr;*/
}

const char* Entity::GetFaceInString(int face)
{
	const char* txt = "";

	switch (face)
	{
	case Face::NONE:
		txt = "None";
		break;

	case Face::Front:
		txt = "Front";
		break;

	case Face::Back:
		txt = "Back";
		break;

	case Face::Top:
		txt = "Top";
		break;

	case Face::Down:
		txt = "Down";
		break;

	case Face::Left:
		txt = "Left";
		break;

	case Face::Right:
		txt = "Right";
		break;

	default:
		txt = "None";
		break;
	}

	return txt;
}

bool Entity::IsColliding(Entity* pOther)
{
	if (m_Tag == -1 || pOther->GetTag() == -1)
	{
		std::cout << "Some tags didn't get set !\n";
	}
	else if (App::Get()->GetSceneManager()->GetCurrentScene()->IsAllowedToCollide(m_Tag, pOther->GetTag()) == false)
	{
		return false;
	}

	gce::Vector3f32 myPos = GetPosition();
	gce::Vector3f32 otherPos = pOther->GetPosition();

	gce::Vector3f32 mySize = GetScale();
	gce::Vector3f32 otherSize = pOther->GetScale(); 

	gce::Vector3f32 myHalfScale = GetScale() * 0.5f;
	gce::Vector3f32 otherHalfScale = pOther->GetScale() * 0.5f;

	if (myPos.x + mySize.x * 0.5f >= otherPos.x - otherSize.x * 0.5f && myPos.x - mySize.x * 0.5f <= otherPos.x + otherSize.x * 0.5f)
	{
		if (myPos.y + mySize.y * 0.5f >= otherPos.y - otherSize.y * 0.5f && myPos.y - mySize.y * 0.5f <= otherPos.y + otherSize.y * 0.5f)
		{
			if (myPos.z + mySize.z * 0.5f >= otherPos.z - otherSize.z * 0.5f && myPos.z - mySize.z * 0.5f <= otherPos.z + otherSize.z * 0.5f)
			{
				float dx = otherPos.x - myPos.x;
				float dy = otherPos.y - myPos.y;
				float dz = otherPos.z - myPos.z;

				float penX = (myHalfScale.x + otherHalfScale.x) - abs(dx);
				float penY = (myHalfScale.y + otherHalfScale.y) - abs(dy);
				float penZ = (myHalfScale.z + otherHalfScale.z) - abs(dz);

				if (penX <= penY && penX <= penZ)
				{
					if (dx > 0)
					{
						SetFace(Face::Right);
						pOther->SetFace(Face::Left);
					}
					else
					{
						SetFace(Face::Left);
						pOther->SetFace(Face::Right);
					}
				}
				else if(penY <= penX && penY <= penZ)
				{
					if (dy >= 0)
					{
						SetFace(Face::Top);
						pOther->SetFace(Face::Down);
					}
					else
					{
						SetFace(Face::Down);
						pOther->SetFace(Face::Top);
					}
				}
				else
				{
					if (dz >= 0)
					{
						SetFace(Face::Back);
						pOther->SetFace(Face::Front);
					}
					else
					{
						SetFace(Face::Front);
						pOther->SetFace(Face::Back);
					}
				}

				return true;
			}
		}
	}

	return false;
}

void Entity::OnCollision(Entity* pOther)
{
}
