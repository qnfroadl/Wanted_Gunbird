#include "EnemyMissileManager.h"
#include "EnemyMissile.h"
#include "MissilePattern.h"
#include "TimerManager.h"
#include "CommonFunction.h"

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
	for (auto it = listMissiles.begin(); it != listMissiles.end(); it++)
	{
		(*it)->Release();
		delete (*it);
	}
	listMissiles.clear();
}

void EnemyMissileManager::Update()
{
	float accumulatedTime = TimerManager::GetInstance()->GetAccumulatedTime();
	
	for (MissileInfo info : vecMissileInfo)
	{
		if (info.fireDelay > accumulatedTime)
		{			
			EnemyMissile* missile = new EnemyMissile(info.speed, info.angle);
			//std::unique_ptr<EnemyMissile> missile = std::make_unique<EnemyMissile>(info.speed, info.angle);

			missile->Init("Mid Boss Missile", TEXT("assets/Sprites/Enemies/boss_ball_one.bmp"), info.startPos, 5, 5, 1, 1, true, RGB(255, 255, 255));

			listMissiles.push_back((missile));
			//listMissiles.push_back(std::move(missile));
		}
	}

	for (auto it = listMissiles.begin(); it != listMissiles.end(); it++)
	{
		(*it)->Update();
	}
}

void EnemyMissileManager::Render(HDC hdc)
{
	for (auto it = listMissiles.begin(); it != listMissiles.end();)
	{
		if (IsOutofScreen((*it)->getRect(), 0.0f))
		{
			(*it)->Release();
			delete (*it);
			it = listMissiles.erase(it);
		}
		else
		{
			(*it)->Render(hdc);
			it++;
		}
	}
}
