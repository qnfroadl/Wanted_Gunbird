#include "EnemyManager.h"
#include  "Enemy.h"
#include "ImageManager.h"


Enemy* EnemyManager::CreateEnemy(EEnemyType enemyType)
{
	// 타입에 따른 적 생성.
	EnemyImgInfo info = enemyInfoMap[enemyType];
	Enemy* enemy = new Enemy(info.hp);
	enemy->Init(
		info.key,
		info.filePath,
		info.width,
		info.height,
		info.maxFrameX,
		info.maxFrameY,
		info.isTransparent,
		info.transColor);

	return enemy;
}

void EnemyManager::InitEnemy()
{
	enemyInfoMap[EEnemyType::MidBoss] = { EImageKey::MidBoss, 
		TEXT("assets/Sprites/Enemies/MidBoss_Idle.bmp"), 200, 410.0f * 1.5, 73.0f * 1.5, 5, 1, true, RGB(255, 0, 255) };
	ImageManager::GetInstance()->AddImage(EImageKey::MidBossUpgrade, 
		TEXT("assets/Sprites/Enemies/MidBossUpgrade.bmp"), 552.0f * 1.5, 91.0f * 1.5, 6, 1, true, RGB(255, 0, 255));
}

bool EnemyManager::IsLiveEnmey()
{
	return !enemys.empty();
} 

void EnemyManager::Init()
{
	// enemy들 정보 초기화
	InitEnemy();
	
	SpawnEnemy(FPOINT{300.0, 100.0}, EEnemyType::MidBoss);
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

void EnemyManager::SpawnEnemy(const FPOINT& pos, EEnemyType enemyType)
{
	Enemy* enemy = CreateEnemy(enemyType);
	if (nullptr != enemy)
	{
		enemy->SetPos(pos);
		enemys.push_back(enemy);
	}
}