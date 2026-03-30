#include "pch.h"
#include "TileGenerator.h"
#include "Tile.h"
#include "RunnerScene.h"

void TileGenerator::InitFirst()
{
	AddTile(3)->CreateFloor(nullptr);
}

Tile* TileGenerator::AddTile(int linesNb)
{
	m_Offset += Tile_Size * linesNb;

	Tile* t = new Tile(linesNb);
	t->SetOffset(m_Offset);

	m_pTiles.push_back(t);

	return t;
}

void TileGenerator::Clear()
{
	m_Offset = -Tile_Size * 3.f;

	for (Tile* t : m_pTiles)
	{
		delete t;
	}

	m_pTiles.clear();
}

void TileGenerator::DestroyLastTile()
{
	if (m_pTiles.empty())
		return;

	auto it = m_pTiles.begin();

	delete* it;

	it = m_pTiles.erase(it);
}

Tile* TileGenerator::GetCurrentTile()
{
	return *(m_pTiles.rbegin()); // Return the last added tile
}

Tile* TileGenerator::GetLastTile()
{
	if (m_pTiles.empty())
		return nullptr;

	return *(m_pTiles.begin()); // Return the first tile
}
