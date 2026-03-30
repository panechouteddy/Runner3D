#include "pch.h"
#include "Tile.h"
#include "Entity.h"
#include "App.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RunnerScene.h"
#include "Ressources.h"

#include "Floor.h"
#include "Wall.h"
#include "Coins.h"
#include "PowerUp.h"

#include "StaticEnnemi.h"
#include "MoveEnnemy.h"
#include "CrazyFrogEnnemy.h"

constexpr float WALL_SIZE_Z = 5.f;

void Tile::HandlePowerUpConfig(int configNb, gce::Vector3f32 center)
{
	if (configNb == (int)PowerBall::NONE)
	{
		return;
	}
	if (configNb == (int)PowerBall::SHIELD)
	{
		PowerUp* p = new ShieldBall();

		p->SetPosition(m_Center + center);

		m_pEntities.push_back(p);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(p);

		return;
	}
	if (configNb == (int)PowerBall::DOUBLEJUMP)
	{
		PowerUp* p = new DoubleJumpBall();

		p->SetPosition(m_Center + center);

		m_pEntities.push_back(p);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(p);

		return;
	}
	if (configNb == (int)PowerBall::SPEED)
	{
		PowerUp* p = new SpeedBall();

		p->SetPosition(m_Center + center);

		m_pEntities.push_back(p);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(p);

		return;
	}
}

void Tile::HandleFullConfig(int configNb, gce::Vector3f32 center)
{
	// WALLS /////////////////////////////////////////
	if (configNb == Editor::Wall::Low)
	{
		float wallHeight = 10.f;

		Wall* pWall = new Wall();

		pWall->SetScale({ Tile_Size * 0.9f, wallHeight, WALL_SIZE_Z });
		pWall->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall);

		return;
	}
	if (configNb == Editor::Wall::High)
	{
		float wallHeight = 30.f;

		Wall* pWall = new Wall();

		pWall->SetScale({ Tile_Size * 0.9f, wallHeight, WALL_SIZE_Z });
		pWall->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall);

		return;
	}
	if (configNb == Editor::Wall::Under)
	{
		float wallHeight = 20.f;

		float mainWallSizeX = Tile_Size * 0.9f;

		Wall* pWall = new Wall();

		pWall->SetScale({ mainWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + wallHeight * 0.5f + 10.f, m_Center.z + center.z });

		m_pEntities.push_back(pWall);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall);

		//////////////////////////////////////////////

		float bordWallSizeX = Tile_Size * 0.1f;

		Wall* pWall2 = new Wall();

		pWall2->SetScale({ bordWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall2->SetPosition({ m_Center.x + center.x + (bordWallSizeX - mainWallSizeX) * 0.5f, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall2);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall2);

		Wall* pWall3 = new Wall();

		pWall3->SetScale({ bordWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall3->SetPosition({ m_Center.x + center.x - (bordWallSizeX - mainWallSizeX) * 0.5f, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall3);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall3);

		return;
	}
	if (configNb == Editor::Wall::UnderOver)
	{
		float wallHeight = 5.f;

		float mainWallSizeX = Tile_Size * 0.9f;

		Wall* pWall = new Wall();

		pWall->SetScale({ mainWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + wallHeight * 0.5f + 5.f, m_Center.z + center.z });

		m_pEntities.push_back(pWall);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall);

		//////////////////////////////////////////////

		float bordWallSizeX = Tile_Size * 0.1f;

		Wall* pWall2 = new Wall();

		pWall2->SetScale({ bordWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall2->SetPosition({ m_Center.x + center.x + (bordWallSizeX - mainWallSizeX) * 0.5f, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall2);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall2);

		Wall* pWall3 = new Wall();

		pWall3->SetScale({ bordWallSizeX, wallHeight, WALL_SIZE_Z });
		pWall3->SetPosition({ m_Center.x + center.x - (bordWallSizeX - mainWallSizeX) * 0.5f, m_Center.y + center.y + wallHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pWall3);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pWall3);

		return;
	}

	// COINS /////////////////////////////////////////
	float coinHeight = 5.f;

	if (configNb == Editor::Coin::One)
	{
		Coins* pCoin = new Coins();

		pCoin->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + coinHeight, m_Center.z + center.z });

		m_pEntities.push_back(pCoin);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pCoin);

		return;
	}
	if (configNb == Editor::Coin::Straight)
	{
		for (int i = -1; i < 2; i++)
		{
			Coins* pCoin = new Coins();

			pCoin->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + coinHeight, m_Center.z + center.z + i * Tile_Size / 4.f });

			m_pEntities.push_back(pCoin);
			App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pCoin);
		}

		return;
	}
	if (configNb == Editor::Coin::Horizontal)
	{
		for (int i = -1; i < 2; i++)
		{
			Coins* pCoin = new Coins();

			pCoin->SetPosition({ m_Center.x + center.x + i * Tile_Size / 4.f , m_Center.y + center.y + coinHeight, m_Center.z + center.z });

			m_pEntities.push_back(pCoin);
			App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pCoin);
		}

		return;
	}
	// MOBS //////////////////////////////////////////

	if (configNb == Editor::Mob::Static)
	{
		float MobHeight = -4.f;

		StaticEnnemy* pEnemy = new StaticEnnemy();
		pEnemy->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + MobHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pEnemy);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pEnemy);

		return;
	}
	if (configNb == Editor::Mob::Moving)
	{
		MoveEnnemy* pEnemy = new MoveEnnemy();

		pEnemy->SetPosition({ m_Center.x + center.x, m_Center.y + center.y, m_Center.z + center.z});

		m_pEntities.push_back(pEnemy);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pEnemy);

		return;
	}
	if (configNb == Editor::Mob::CrazyF)
	{
		float MobHeight = 15.f;

		CrazyFrogEnnemy* pEnemy = new CrazyFrogEnnemy();
		pEnemy->SetPosition({ m_Center.x + center.x, m_Center.y + center.y + MobHeight * 0.5f, m_Center.z + center.z });

		m_pEntities.push_back(pEnemy);
		App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pEnemy);

		return;
	}
}

Tile::Tile(int linesNb)
{
	m_Size = linesNb * 3;
}

Tile::~Tile()
{
	for (Entity* e : m_pEntities)
	{
		e->m_ToDestroy = true;
	}

	delete m_OccupedPlaces;

	m_OccupedPlaces = nullptr;
}

Tile* Tile::CreateFloor(int* config, float height)
{
	m_OccupedPlaces = new bool[m_Size];

	m_Center = { 0.f, height, m_Offset };

	int line = -1;
	int column = -1;
	int countToAlign = 0;
	int count = 0;

	if (config == nullptr) // Every Floor is 1 
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (countToAlign >= 3)
			{
				line++;
				column = -1;
				countToAlign = 0;
			}

			m_OccupedPlaces[i] = false;

			Entity* pCube = new Floor();
			pCube->SetScale({ Tile_Size, Floor_Height, Tile_Size });

			pCube->SetPosition(m_Center + gce::Vector3f32(m_Mirrored * -column * Tile_Size, 0.f, -line * Tile_Size));

			m_pEntities.push_back(pCube);
			App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pCube);

			column++;
			countToAlign++;
			count++;
		}
	}
	else
	{
		for (int i = 0; i < m_Size; i++)
		{
			if (countToAlign >= 3)
			{
				line++;
				column = -1;
				countToAlign = 0;
			}


			if (config[i] == 0)
			{
				m_OccupedPlaces[i] = true;
			}

			if (config[i] == 1)
			{
				m_OccupedPlaces[i] = false;

				Entity* pCube = new Floor();
				pCube->SetScale({ Tile_Size, Floor_Height, Tile_Size });

				pCube->SetPosition(m_Center + gce::Vector3f32(m_Mirrored * -column * Tile_Size, 0.f, -line * Tile_Size));

				m_pEntities.push_back(pCube);
				App::Get()->GetSceneManager()->GetCurrentScene()->ToAdd(pCube);
			}

			column++;
			countToAlign++;
			count++;
		}

	}

	return this;
}

Tile* Tile::CreatePowerUp(int* config, float height)
{
	if (config == nullptr)
		return this;

	int line = -1;
	int column = -1;
	int count = 0;

	for (int i = 0; i < m_Size; i++)
	{
		if (count >= 3)
		{
			line++;
			column = -1;
			count = 0;
		}

		float powerHeight = 10.f;

		if (config[i] >= 1)
		{
			m_OccupedPlaces[i] = true;

			int powerConfigNb = config[i];

			if (powerConfigNb < (int)PowerBall::NONE)
				powerConfigNb = (int)PowerBall::NONE;
			else if (powerConfigNb >= (int)PowerBall::Count)
				powerConfigNb = (int)PowerBall::NONE;

			HandlePowerUpConfig(powerConfigNb, gce::Vector3f32(m_Mirrored * -column * Tile_Size, height + (Floor_Height + powerHeight) * 0.5f, -line * Tile_Size));
		}

		column++;
		count++;
	}

	return this;
}

Tile* Tile::CreateFullConfig(int* config, float height)
{
	if (config == nullptr)
		return this;

	int line = -1;
	int column = -1;
	int count = 0;

	for (int i = 0; i < m_Size; i++)
	{
		if (count >= 3)
		{
			line++;
			column = -1;
			count = 0;
		}

		if (config[i] != __)
		{
			m_OccupedPlaces[i] = true;
			HandleFullConfig(config[i], gce::Vector3f32(m_Mirrored * -column * Tile_Size, height + (Floor_Height) * 0.5f, -line * Tile_Size));
		}

		column++;
		count++;
	}


	return this;
}
