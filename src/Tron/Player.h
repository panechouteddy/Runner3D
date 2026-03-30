#pragma once

#include "Entity.h"
#include "Collider.h"
#include "lib/Inputs/InputsMethods.h" // Ensure this header is included for sr::Keyboard

class TronManager;

class Player : private Entity, public Collider
{
	TronManager* m_pGameManager;

	gce::Vector3f32 m_Direction;
	gce::Vector3f32 m_Position;

	int m_Speed;
	int m_PlayerID;

	gce::Vector3f32 m_LastTrailPos;
	float m_TrailDelay = 0.5f;

	sr::Keyboard::Key left = sr::Keyboard::LEFT_ARROW;
	sr::Keyboard::Key right = sr::Keyboard::RIGHT_ARROW;
	sr::Keyboard::Key up = sr::Keyboard::UP_ARROW;
	sr::Keyboard::Key down = sr::Keyboard::DOWN_ARROW;

public:
	void Init() override;
	void SetGameManager(TronManager* gameManager);

	void OnCollision() override;

	void Update(float deltaTime) override;

	gce::Vector3f32 GetDirection() { return m_Direction; }
	gce::Vector3f32 GetPosition() { return m_Position; }
	gce::Vector3f32 GetLastTrailPos() { return m_LastTrailPos; }
	int GetPlayerID() { return m_PlayerID; }	

	void SetPlayer2();
};

