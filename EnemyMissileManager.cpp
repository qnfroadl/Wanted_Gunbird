#include "EnemyMissileManager.h"
#include "EnemyMissile.h"


EnemyMissileManager::EnemyMissileManager()
{
}

EnemyMissileManager::~EnemyMissileManager()
{
}

void EnemyMissileManager::Fire(FPOINT pos, float angle, MissileType* type)
{
}

void EnemyMissileManager::Fire(FPOINT pos, MissilePattern* pattern)
{
}

void EnemyMissileManager::Init()
{
	EnemyMissile* missile = new EnemyMissile;

	missile->Init("Mid Boss", TEXT("assets/Sprites/Enemies/boss_dragon_death.bmp"),
		30, 30, 1, 1, true, RGB(255, 255, 255));
	vecMissiles.push_back(missile);
}

void EnemyMissileManager::Release()
{
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Release();
		delete vecMissiles[i];
	}
	vecMissiles.clear();
}

void EnemyMissileManager::Update()
{
	for (int i = 0; i < vecMissiles.size(); i++)
		vecMissiles[i]->Update();
}

void EnemyMissileManager::Render(HDC hdc)
{
	for (int i = 0; i < vecMissiles.size(); i++)
		vecMissiles[i]->Render(hdc);
}
