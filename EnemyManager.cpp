#include "EnemyManager.h"
#include  "Enemy.h"


Enemy* EnemyManager::CreateEnemy(int enemyType)
{
	// Ÿ�Կ� ���� �� ����.
	Enemy* enemy = new Enemy(10); // hp
	enemy->Init("Mid Boss", TEXT("assets/Sprites/Enemies/MidBoss_Idle.bmp"),
		410, 73, 5, 1, true, RGB(255, 0, 255));

	return enemy;
}

bool EnemyManager::IsLiveEnmey()
{
	return !enemys.empty();
} 

void EnemyManager::Init()
{
	SpawnEnemy(FPOINT{300.0, 100.0}, 1);
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
			enemy->Release();
			delete enemy;
			it = enemys.erase(it);
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


