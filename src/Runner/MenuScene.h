#pragma once
#include "Scene.h"

constexpr int BUTTONS_NB = 2;

class ButtonText;

class MenuScene : public Scene
{
	std::vector<ButtonText*> m_Buttons;
	int index = 0;
public:
	void Clear() override;
	void Init() override;
	void Update() override;

};

