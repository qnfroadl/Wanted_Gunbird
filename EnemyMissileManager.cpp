#include "EnemyMissileManager.h"
#include "EnemyMissile.h"
#include "MissilePattern.h"
#include "TimerManager.h"
#include "CommonFunction.h"


void EnemyMissileManager::Fire(FPOINT pos, float angle, MissileType* type)
{
}

void EnemyMissileManager::Fire(FPOINT pos, MissilePattern* pattern)
{
	std::vector<MissileInfo> missilesInfo = pattern->getMissilesInfo();

	// fire 정보 넣어두고 Update 때 조건에 맞으면 fire
	for (int i = 0; i < missilesInfo.size(); i++)
		listMissileInfo.push_back(missilesInfo[i]);
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
		it = listMissiles.erase(it);
	}
}

void EnemyMissileManager::Update()
{
	float accumulatedTime = TimerManager::GetInstance()->GetAccumulatedTime();
	
	// 조건에 맞으면 미사일 생성
	for (auto it = listMissileInfo.begin(); it != listMissileInfo.end();)
	{
		if ((*it).fireDelay > accumulatedTime)
		{						
			EnemyMissile* missile = new EnemyMissile((*it).speed, (*it).angle);
			missile->Init("Mid Boss Missile", TEXT("assets/Sprites/Enemies/MidBoss_Star.bmp"), 
				(*it).startPos, 288, 45, 8, 1, true, RGB(255, 0, 255));
			listMissiles.push_back(missile);	

			// 생성했으면 이 미사일에 대한 정보는 파기
			it = listMissileInfo.erase(it);
		}
		else
		{
			it++;
		}
	}

	// 생성된 모든 미사일 Update
	for (auto it = listMissiles.begin(); it != listMissiles.end(); it++)	
		(*it)->Update();
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

EnemyMissileManager::EnemyMissileManager()
{	
}

EnemyMissileManager::~EnemyMissileManager()
{
}