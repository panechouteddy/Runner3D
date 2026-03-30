#pragma once
#include "lib/Inputs/InputsMethods.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Camera.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include "lib/Text.h"

using namespace gce;

class Entity;
class PhysicManager;
class Collider;

class GameManager
{
protected:
	std::vector<Entity*> mEntity;	
	std::vector<Collider*> mCollider;

	PhysicManager* m_pPhysicManager;

	bool isFinished = false;
	bool isPaused = true;

public:

	virtual void Init();

	virtual void Draw(sr::Window& window);
	virtual void Update(float deltaTime);

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);

	void AddCollider(Collider* entity);
	void RemoveCollider(Collider* entity);
	virtual void CleanAll();

	bool GetPauseStatus() { return isPaused; }
	void SetPauseStatus(bool newValue) { isPaused = newValue; }

	static void Rotate(float angle, sr::Geometry* pGeo, gce::Vector3f32 centre);
};

