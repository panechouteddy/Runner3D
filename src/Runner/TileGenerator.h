#pragma once
#include <vector>
#include "GCSR.h"
#include "Ressources.h"

class Tile;

class TileGenerator
{
	float m_Offset = -Tile_Size * 3.f;
	std::vector<Tile*> m_pTiles;
public:
	void Clear();
	void InitFirst();
	Tile* AddTile(int linesNb);
	void DestroyLastTile();
	Tile* GetCurrentTile();
	Tile* GetLastTile();
};

