#include "pch.h"
#include "RunnerCamera.h"
#include "App.h"
#include "Entity.h"

constexpr int ZPOSITION = -50;
constexpr int YPOSITION = 50;
void RunnerCamera::Init()
{
	m_pCamera = new sr::Camera(sr::CameraType::PERSPECTIVE);
	m_pCamera->SetPosition({ 0.f, 0.f, 0.f });
	m_pCamera->SetRotation({ 0.f, 0.0f, 0.0f });
	m_pCamera->SetFOV(gce::PI / 2.0f);
	m_pCamera->SetFarPlane(1000.f);
	m_pCamera->SetNearPlane(0.1f);
}
void RunnerCamera::Update()
{

}

void RunnerCamera::FollowEntity(Entity* e, gce::Vector3f32 offset, gce::Vector3f32 followAxis)
{
	if (e == nullptr)
		return;

	gce::Vector3f32 camPos = GetPosition();
	gce::Vector3f32 entityPos = e->GetPosition();

	if (followAxis.x < 1)
	{
		entityPos.x = camPos.x - offset.x;
	}

	if (followAxis.y < 1)
	{
		entityPos.y = camPos.y - offset.y;
	}

	if (followAxis.z < 1)
	{
		entityPos.z = camPos.z - offset.z;
	}

	gce::Vector3f32 finalPos = entityPos + offset;

	m_pCamera->SetPosition(finalPos);
}
