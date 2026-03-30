#pragma once
#include "GCSR.h"
#include <vector>

class Entity;

class Tile
{
	int m_Size = 0;
	float m_Offset = 0.f;
	gce::Vector3f32 m_Center = { 0.f, 0.f, 0.f };
	std::vector<Entity*> m_pEntities;
	int m_Mirrored = -1;

	bool* m_OccupedPlaces;

	void HandlePowerUpConfig(int configNb, gce::Vector3f32 center);
	void HandleFullConfig(int configNb, gce::Vector3f32 center); // PROTO
public:
	Tile(int linesNb);
	~Tile();

	void SetOffset(float val) { m_Offset = val; }
	void SetMirrored() { m_Mirrored = -1; }
	gce::Vector3f32 GetCenter() { return m_Center; }

	int GetSize() { return m_Size; }

	bool* GetOccupedPlaces() { return m_OccupedPlaces; }

	Tile* CreateFloor(int* config, float height = 0.f);
	Tile* CreatePowerUp(int* config, float height = 0.f);

	Tile* CreateFullConfig(int* config, float height = 0.f); // PROTO
};

