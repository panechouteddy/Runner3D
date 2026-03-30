#include "pch.h"
#include "RandomConfigGenerator.h"
#include "Tile.h"
#include "TileGenerator.h"
#include "PowerUp.h"

RandomConfigGenerator::RandomConfigGenerator(TileGenerator* ref)
{
	m_TileGenerator = ref;

	InitConfigs();
}

RandomConfigGenerator::~RandomConfigGenerator()
{
	for (auto it = m_FloorConfigs.begin(); it != m_FloorConfigs.end(); ++it)
	{
		delete it->second;
	}

	m_FloorConfigs.clear();

	for (auto it = m_FullConfigs.begin(); it != m_FullConfigs.end(); ++it)
	{
		delete it->second;
	}

	m_FullConfigs.clear();
}

void RandomConfigGenerator::InitConfigs()
{
	// 3 Lines = 3L = default

	// Config 1 | Nothing
	{
		const int size = 9;

		int* fullConfig = new int[size]
		{
			__, CO, __,
			__, CO, __,
			__, CO, __
		};

		AddConfig(size, nullptr, fullConfig);
	}

	// Config 2 | The Hole
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 1, 1,
				1, 0, 1,
				1, 1, 1
			};

		int* fullConfig = new int[size]
		{
			CS, MF, CS,
			WL, __, WL,
			__, __, __
		};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 3 - The missing Middle
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 0, 1,
				1, 0, 1,
				1, 0, 1
			};

		int* fullConfig = new int[size]
		{
			WL, __, WL,
			CH, __, CH,
			WL, __, WL
		};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 4 | The X
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 0, 1,
				0, 1, 0,
				1, 0, 1
			};

		int* fullConfig = new int[size]
		{
			MS, __, MS,
			__, WL, __,
			__, __, __
		};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 5 | The Big A | 6L
	{
		const int size = 18;

		int* floorConfig = new int[size]
			{
				1, 1, 1,
				1, 0, 1,
				1, 0, 1,
				1, 1, 1,
				1, 0, 1,
				1, 0, 1
			};

		int* fullConfig = new int[size]
		{
			CS, WH, CS,
			MM, __, WL,
			CO, __, CO,
			CO, WH, MM,
			__, __, __,
			CO, __, CO
		};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 6 | The missing Side | 4L
	{
		const int size = 12;

		int* floorConfig = new int[size]
			{
				1, 1, 0,
				1, 1, 0,
				1, 1, 0,
				1, 1, 0
			};

		int* fullConfig = new int[size]
			{
				CO, WL, __,
				WL, CO, __,
				CO, WL, __,
				WL, CO, __
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 7 | The Bridge
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				0, 0, 0,
				1, 1, 1,
				0, 1, 0
			};

		int* fullConfig = new int[size]
			{
				__, __, __,
				CO, CO, CH,
				__, __, __
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 8 | The +
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				0, 1, 0,
				1, 1, 1,
				0, 1, 0
			};

		int* fullConfig = new int[size]
			{
				__, MF, __,
				CS, WH, MM,
				__, __, __
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 9 | The O | 4L
	{
		const int size = 12;

		int* floorConfig = new int[size]
			{
				0, 1, 0,
				1, 0, 1,
				1, 0, 1,
				0, 1, 0
			};

		int* fullConfig = new int[size]
			{
				__, MF, __,
				WL, __, WL,
				CO, __, CH,
				__, WH, __
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 10 | The diagonal wall
	{
		const int size = 9;

		int* fullConfig = new int[size]
			{
				WH, CS, __,
				CS, WH, CO,
				__, CO, WH
			};

		AddConfig(size, nullptr, fullConfig);
	}

	// Config 11 | The arrow
	{
		const int size = 15;

		int* fullConfig = new int[size]
			{
				WH, __, __,
				CS, WH, CO,
				__, __, WH,
				CS, WH, CO,
				WH, __, __
			};

		AddConfig(size, nullptr, fullConfig);
	}

	// Config 12 | The Elbow
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 0, 0,
				1, 0, 0,
				1, 1, 1
			};

		int* fullConfig = new int[size]
			{
				WL, __, __,
				MS, __, __,
				__, CS, MF
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 13 | The Reverse Elbow
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 1, 1,
				0, 0, 1,
				0, 0, 1
			};

		int* fullConfig = new int[size]
			{
				MF, MS, CO,
				__, __, __,
				__, __, WH
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 14 | The 4 Isles
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 0, 1,
				0, 0, 0,
				1, 0, 1
			};

		int* fullConfig = new int[size]
			{
				CH, __, MS,
				__, __, __,
				MM, __, CO
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 15 | The H
	{
		const int size = 9;

		int* floorConfig = new int[size]
			{
				1, 0, 1,
				1, 1, 1,
				1, 0, 1
			};

		int* fullConfig = new int[size]
			{
				CS, __, CO,
				WH, CO, WH,
				MF, __, MM
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 16 | The Facing Elbows
	{
		const int size = 15;

		int* floorConfig = new int[size]
			{
				1, 1, 1,
				1, 0, 0,
				1, 0, 1,
				0, 0, 1,
				1, 1, 1
			};

		int* fullConfig = new int[size]
			{
				CO, MF, CH,
				__, __, __,
				WH, __, WH,
				__, __, __,
				CH, __, CO
			};

		AddConfig(size, floorConfig, fullConfig);
	}

	// Config 17 | The Double Tetris
	{
		const int size = 15;

		int* floorConfig = new int[size]
			{
				1, 0, 0,
				1, 1, 0,
				1, 0, 1,
				0, 1, 1,
				0, 0, 1
			};

		int* fullConfig = new int[size]
			{
				__, MM, __,
				WL, CH, __,
				__, __, __,
				__, CH, WL,
				__, __, __
			};

		AddConfig(size, floorConfig, fullConfig);
	}
	// Config 18 | The Static Hell | 6L
	{
		const int size = 18;

		int* floorConfig = new int[size]
			{
					0, 1, 1,
					1, 0, 1,
					1, 1, 1,
					0, 0, 1,
					1, 0, 1,
					1, 1, 0
			};

		int* fullConfig = new int[size]
			{
					__, CO, CO,
					MS, __, MS,
					__, MS, CH,
					__, __, __,
					MS, __, MS,
					CO, CO, __,
			};

		AddConfig(size, floorConfig, fullConfig);
	}
	// Config 19 | Its frogging Time | 6L
	{
		const int size = 18;

		int* floorConfig = new int[size]
			{
					1, 0, 1,
					0, 1, 0,
					1, 1, 0,
					0, 1, 1,
					1, 0, 1,
					1, 1, 1
			};

		int* fullConfig = new int[size]
			{
					WH, __, CS,
					__, __, __,
					CS, WL, __,
					__, __, WL,
					MF, __, MF,
					CO, MF, CH,
			};

		AddConfig(size, floorConfig, fullConfig);
	}
	// Config 20 | Final move attack | 6L
	{
		const int size = 18;

		int* floorConfig = new int[size]
			{
					1, 0, 1,
					0, 1, 1,
					1, 1, 0,
					1, 0, 1,
					1, 0, 1,
					0, 1, 0
			};

		int* fullConfig = new int[size]
			{
					MM, __, CS,
				    __, CS, MM,
					CS, MM, __,
					MM, __, CO,
					CO, __, MM,
					__, MM, __,
			};

		AddConfig(size, floorConfig, fullConfig);
	}
}


void RandomConfigGenerator::GenerateRandomConfig()
{
	int max = m_FloorConfigs.size();

	bool mirrored = rand() % 2;

	int random = rand() % max;

	Tile* t = m_TileGenerator->AddTile(m_ConfigLinesCount[random]);
	
	if (mirrored == true)
	{
		t->SetMirrored();
	}

	t->CreateFloor(m_FloorConfigs[random])->CreateFullConfig(m_FullConfigs[random]);

	HandleRandomPowerUp();
}

void RandomConfigGenerator::HandleRandomPowerUp()
{
	static int pity = 0; // If you are very unlucky :3

	int seed = rand() % 101;

	if (seed + pity < 80)
	{
		pity += 3;
		return;
	}
	else
	{
		pity = 0;
	}

	int rdmPowerUp = 1 + rand() % (int)PowerBall::Count;

	Tile* pCurrent = m_TileGenerator->GetCurrentTile();

	int size = pCurrent->GetSize();

	int* config = new int[size];
	for (int i = 0; i < size; i++)
	{
		config[i] = 0;
	}

	std::vector<int> freePlaces;

	bool* occupedPlaces = pCurrent->GetOccupedPlaces();
	for (int i = 0; i < size; i++)
	{
		if (occupedPlaces[i] == false)
		{
			freePlaces.push_back(i);
		}
	}

	if (freePlaces.empty() == false)
	{        
		int randomPlace = freePlaces[rand() % freePlaces.size()];

		config[randomPlace] = rdmPowerUp;

		pCurrent->CreatePowerUp(config);
	}

	freePlaces.clear();
}

void RandomConfigGenerator::AddConfig(int size, int* floors, int* config)
{
	m_ConfigLinesCount[m_i] = size / 3;
	m_FloorConfigs[m_i] = floors;
	m_FullConfigs[m_i] = config;

	m_i++;
}
