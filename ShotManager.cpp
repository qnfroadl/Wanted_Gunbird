#include "ShotManager.h"
#include "Shot.h"
#include "CommonFunction.h"
#define SHOT_COUNT 100


void ShotManager::Init()
{
	Shot* shot = nullptr;
	vecShots.reserve(SHOT_COUNT);
	activeShots.reserve(SHOT_COUNT);
	for (int i = 0; i < SHOT_COUNT; i++)
	{
		shot = new Shot();
		shot->Init();
		shot->SetActive(false);

		vecShots.push_back(shot);
	}

	curIt = vecShots.begin();
}

void ShotManager::Update()
{
	if (0 < activeShots.size())
	{
		Shot* shot = nullptr;
		auto it = activeShots.begin();
		while (it != activeShots.end())
		{
			shot = (*it);
			if (shot->IsActive())
			{
				shot->Update();

				if (IsOutofScreen(shot->GetPos()))
				{
					shot->SetActive(false);
					it = activeShots.erase(it);
					continue;
				}
			}
			else 
			{
				it = activeShots.erase(it);
				continue;
			}
			it++;
		}
	}
}

void ShotManager::Render(HDC hdc)
{
	if (0 < activeShots.size())
	{
		Shot* shot = nullptr;
		auto it = activeShots.begin();
		while (it != activeShots.end())
		{
			shot = *it;
			shot->Render(hdc);
			it++;
		}
	}
}

void ShotManager::Release()
{
	activeShots.clear();

	auto it = vecShots.begin();
	Shot* shot = nullptr;
	while (it != vecShots.end())
	{
		shot = *it;
		shot->Release();
		delete shot;
		it++;
	}

	vecShots.clear();
}

void ShotManager::ClearAllShot()
{
	auto it = vecShots.begin();
	Shot* shot = nullptr;
	while (it != vecShots.end())
	{
		shot = *it;
		shot->SetActive(false);

		it++;
	}
}

void ShotManager::Fire(float x, float y, float angle, float speed)
{
	this->Fire(FPOINT{x,y}, angle, speed);
}

void ShotManager::Fire(const FPOINT& pos, float angle, float speed)
{
	Shot* shot = nullptr;
	int findCount = 0;

	while (curIt != vecShots.end() && findCount < SHOT_COUNT)
	{
		findCount++;

		shot = *curIt;
		if (shot->IsActive() == false)
		{
			// 발사 가능한 총알이다.
			
			shot->SetSpeed(speed);
			shot->Fire(pos,angle);
			activeShots.push_back(shot);
			break;
		}

		curIt++;
		if (curIt == vecShots.end())
		{	
			curIt = vecShots.begin();
		}
	}

}
