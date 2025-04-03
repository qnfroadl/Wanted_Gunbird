#include "EnemyMissileManager.h"
#include "EnemyMissile.h"
#include "MissilePattern.h"
#include "TimerManager.h"
#include "CommonFunction.h"


void EnemyMissileManager::InitMissile()
{
	missileImgInfoMap[EEnemyType::MidBoss] = { EImageKey::MidBossStar,
		TEXT("assets/Sprites/Enemies/MidBoss_Star.bmp"), 288, 45, 8, 1, true, RGB(255, 0, 255) };
}


void EnemyMissileManager::Fire(FPOINT pos, float angle, MissileType* type)
{
}

void EnemyMissileManager::Fire(FPOINT pos, MissilePattern* pattern)
{
	std::vector<SpawnMissileInfo> missilesInfo = pattern->getMissilesInfo();
	
	for (int i = 0; i < missilesInfo.size(); i++)
		listMissileInfo.push_back(missilesInfo[i]);
}

void EnemyMissileManager::Init()
{
	InitMissile();
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
		
	for (auto it = listMissileInfo.begin(); it != listMissileInfo.end();)
	{
		// 조건에 맞으면 미사일 새로 만들기
		if ((*it).fireDelay > accumulatedTime)
		{						
			EnemyMissile* missile = CreateMissile(EEnemyType::MidBoss, &(*it));
			listMissiles.push_back(missile);				
			it = listMissileInfo.erase(it);
		}
		else
		{
			it++;
		}
	}
	
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

EnemyMissile* EnemyMissileManager::CreateMissile(EEnemyType enemyType, SpawnMissileInfo* it)
{
	// 적 타입에 따른 미사일 생성.	
	EnemyMissile* missile = new EnemyMissile((*it).speed, (*it).angle);
	MissileImgInfo info = missileImgInfoMap[enemyType];
	missile->Init(
		info.key,
		info.filePath,
		(*it).startPos,
		info.width,
		info.height,
		info.maxFrameX,
		info.maxFrameY,
		info.isTransparent,
		info.transColor);	

	return missile;
}

EnemyMissileManager::EnemyMissileManager()
{	
}

EnemyMissileManager::~EnemyMissileManager()
{
}

