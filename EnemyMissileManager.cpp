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

	// fire ���� �־�ΰ� Update �� ���ǿ� ������ fire
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
	
	// ���ǿ� ������ �̻��� ����
	for (auto it = listMissileInfo.begin(); it != listMissileInfo.end();)
	{
		if ((*it).fireDelay > accumulatedTime)
		{						
			EnemyMissile* missile = new EnemyMissile((*it).speed, (*it).angle);
			missile->Init("Mid Boss Missile", TEXT("assets/Sprites/Enemies/MidBoss_Star.bmp"), 
				(*it).startPos, 288, 45, 8, 1, true, RGB(255, 0, 255));
			listMissiles.push_back(missile);	

			// ���������� �� �̻��Ͽ� ���� ������ �ı�
			it = listMissileInfo.erase(it);
		}
		else
		{
			it++;
		}
	}

	// ������ ��� �̻��� Update
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