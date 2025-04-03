#include "EnemyMissileManager.h"
#include "EnemyMissile.h"
#include "MissilePattern.h"
#include "TimerManager.h"


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
	std::vector<MissileInfo> missilesInfo = pattern->getMissilesInfo();

	for (int i = 0; i < missilesInfo.size(); i++)
	{
		vecMissileInfo.push_back(missilesInfo[i]);
	}
}

void EnemyMissileManager::Init()
{
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
	float accumulatedTime = TimerManager::GetInstance()->GetAccumulatedTime();
	
	for (const MissileInfo& info : vecMissileInfo)
	{
		if (info.fireDelay > accumulatedTime)
		{			
			EnemyMissile* missile = new EnemyMissile(info.speed, info.angle);

			missile->Init("Mid Boss Missile", TEXT("assets/Sprites/Enemies/boss_ball_one.bmp"), info.startPos, 5, 5, 1, 1, true, RGB(255, 255, 255));

			vecMissiles.push_back(missile);
		}
	}

	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Update();
	}
}

void EnemyMissileManager::Render(HDC hdc)
{
	for (int i = 0; i < vecMissiles.size(); i++)
	{
		vecMissiles[i]->Render(hdc);
	}
}
