#include "EnemyManager.h"
#include  "Enemy.h"


bool EnemyManager::IsOutofScreen()
{

	return false;
}

bool EnemyManager::IsLiveEnmey()
{

	return false;
} 

void EnemyManager::Init()
{
	Enemy* enemy = new Enemy(1);
	
	enemy->Init("Mid Boss", TEXT("assets/Sprites/Enemies/boss_dragon_death.bmp"), 
		100, 100, 1, 1, true, RGB(255, 255, 255));
	enemys.push_back(enemy);
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
	for (int i = 0; i < enemys.size(); i++)
		enemys[i]->Update();
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i<enemys.size(); i++)
		enemys[i]->Render(hdc);
}


