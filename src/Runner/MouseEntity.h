#pragma once
#include"Entity.h"

class MouseEntity : public Entity
{ 
	gce::Vector2f32 m_pos;
public:
	void OnInitialize() override;
	void OnUpdate()override;
};

