#pragma once
#include "GCSR.h"

class Entity;

class RunnerCamera
{
	sr::Camera* m_pCamera;
public:
	void Init() ;
	void Update();

	sr::Camera* GetSRCamera() { return m_pCamera; }
	gce::Vector3f32 GetPosition() { return m_pCamera->GetPosition(); }
	gce::Vector3f32 GetRotation() { return m_pCamera->GetRotation(); }

	void SetPosition(gce::Vector3f32 position) { m_pCamera->SetPosition(position); }
	void Move(gce::Vector3f32 translation) { m_pCamera->Translate(translation); }
	void SetRotation(gce::Vector3f32 rotation) { m_pCamera->SetRotation(rotation); }
	void Rotate(gce::Vector3f32 rotation) { m_pCamera->Rotate(rotation); }

	void SetFOV(float32 fov) { m_pCamera->SetFOV(fov); }
	void SetCameraPlane(float32 nearest, float32 farthest) { m_pCamera->SetFarPlane(farthest); m_pCamera->SetNearPlane(nearest); }
	void FollowEntity(Entity* e, gce::Vector3f32 offset, gce::Vector3f32 followAxis = { 1.f, 1.f, 1.f });
};

