#include "MissileManager.h"
#include "Missile.h"


MissileManager::MissileManager()
{
}

MissileManager::~MissileManager()
{
}

void MissileManager::Fire(FPOINT pos, float angle, MissileType* type)
{
}

void MissileManager::Fire(FPOINT pos, MissilePattern* pattern)
{
}

void MissileManager::Init()
{
	Missile* missile = new Missile;

	missile->Init("Mid Boss", TEXT("assets/Sprites/Enemies/boss_dragon_death.bmp"),
		30, 30, 1, 1, true, RGB(255, 255, 255));
	vecMissiles.push_back(missile);
}

void MissileManager::Release()
{
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Release();
		delete vecMissiles[i];
	}
	vecMissiles.clear();
}

void MissileManager::Update()
{
	for (int i = 0; i < vecMissiles.size(); i++)
		vecMissiles[i]->Update();
}

void MissileManager::Render(HDC hdc)
{
	for (int i = 0; i < vecMissiles.size(); i++)
		vecMissiles[i]->Render();
}
