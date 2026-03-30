#pragma once
#include <map>

class TileGenerator;

class RandomConfigGenerator
{
	int m_i = 0;
	TileGenerator* m_TileGenerator;

	std::map<int, int> m_ConfigLinesCount;
	std::map<int, int*> m_FloorConfigs;
	std::map<int, int*> m_FullConfigs;
public:
	RandomConfigGenerator(TileGenerator* ref);
	~RandomConfigGenerator();
	void InitConfigs();

	void GenerateRandomConfig();
	void HandleRandomPowerUp();
	void AddConfig(int size, int* floors, int* config);
};

