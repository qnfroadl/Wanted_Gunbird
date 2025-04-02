#include "EnemyManager.h"
#include  "Enemy.h"


Enemy* EnemyManager::CreateEnemy(int enemytType)
{
	// 타입에 따른 적 생성.
	Enemy* enemy = new Enemy(1);
	enemy->Init("Mid Boss", TEXT("assets/Sprites/Enemies/boss_dragon_death.bmp"),
		100, 100, 1, 1, true, RGB(255, 255, 255));

	return enemy;
}

bool EnemyManager::IsLiveEnmey()
{
	return !enemys.empty();
} 

void EnemyManager::Init()
{
	
}

void EnemyManager::Release()
{
	for (int i = 0; i < enemys.size(); i++)
	{
		enemys[i]->Release();
		delete enemys[i];
	}
	enemys.clear();
}

void EnemyManager::Update()
{
	Enemy* enemy = nullptr;

	auto it = enemys.begin();
	while (it != enemys.end())
	{
		enemy = (*it);
		if (enemy->IsActive())
		{
			enemy->Update();
		}
		else {
			enemys.erase(it);
			continue;
		}
		it++;
	}
}

void EnemyManager::Render(HDC hdc)
{
	Enemy* enemy = nullptr;

	auto it = enemys.begin();
	while (it != enemys.end())
	{
		enemy = (*it);
		enemy->Render(hdc);
		it++;
	}
}

void EnemyManager::SpawnEnemy(const FPOINT& pos, int enemyType)
{
	Enemy* enemy = CreateEnemy(enemyType);
	if (nullptr != enemy)
	{
		enemy->SetPos(pos);
		enemys.push_back(enemy);
	}
}


