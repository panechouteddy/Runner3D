#pragma once

class Character;

class Controller
{
private:
	Character* m_pOwner = nullptr;

public:
	Controller();
	void Init();
	void Update();
	void HandleMoving();
	void HandleJump();
	void HandleFastFall(); 
	void HandleCamView();
};

