#pragma once
#include "Entity.h"
#include "Ressources.h"

class ButtonText : public Entity
{
	const char* m_SceneToGo = "";

	std::wstring m_Txt = L"";
	gce::Vector2f32 m_Pos = { (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f};
	gce::Color m_Color = gce::Color::Black;

	bool m_Selected = false; 
public:
	ButtonText(std::wstring txt, gce::Vector2f32 offsetCenter, const char* sceneToGo = "");
	void Start() override;
	void Update() override; 

	bool IsSelected() { return m_Selected; }
	void SetSelected(bool state) { m_Selected = state; }

	void ResetColor() { m_Color = gce::Color::Black; }
	void SetColor(gce::Color color) { m_Color = color; }

	void OnTrigger();
};

