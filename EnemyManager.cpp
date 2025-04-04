#include "EnemyManager.h"
#include  "Enemy.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "CommonFunction.h"

Enemy* EnemyManager::CreateEnemy(EEnemyType enemyType)
{
	// 타입에 따른 적 생성.
	EnemyImgInfo info = enemyInfoMap[enemyType];
	Enemy* enemy = new Enemy(info.hp);
	enemy->Init(
		enemyType,
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
	enemyInfoMap[EEnemyType::MidBoss] = { EImageKey::MidBossBasic, 
		TEXT("assets/Sprites/Enemies/MidBoss_Idle.bmp"), 20, 410.0f * 1.5, 73.0f * 1.5, 5, 1, true, RGB(255, 0, 255) };
	ImageManager::GetInstance()->AddImage(EImageKey::MidBossUpgrade, 
		TEXT("assets/Sprites/Enemies/MidBossUpgrade.bmp"), 552.0f * 1.5, 91.0f * 1.5, 6, 1, true, RGB(255, 0, 255));

	enemyInfoMap[EEnemyType::FlyingEnemy] = { EImageKey::FlyingEnemy,
	TEXT("assets/Sprites/Enemies/flying_missile.bmp"), 2, 240.0f, 30.0f, 8, 1, true, RGB(255, 0, 255) };

	enemyInfoMap[EEnemyType::BeeCopter] = { EImageKey::BeeCopter,
	TEXT("assets/Sprites/Enemies/enemy_beecopter.bmp"), 2, 194.0f, 105.0f, 3, 1, true, RGB(255, 255, 255) };

	//SpawnEnemy(FPOINT{ 300.0f, 100.0f }, EEnemyType::MidBoss);
}

bool EnemyManager::IsLiveEnmey()
{
	return !enemys.empty();
} 

void EnemyManager::Init()
{
	// enemy들 정보 초기화
	InitEnemy();
	generateTime = 0.0f;
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
	// Enemy 일정시간마다 스폰
	generateTime += TimerManager::GetInstance()->GetDeltaTime();
	if (generateTime > 1.0f)
	{
		int x = rand() % WINSIZE_X;
		int y = rand() % (WINSIZE_Y/2);
		//SpawnEnemy(FPOINT{ float(x), 50.0 }, EEnemyType::FlyingEnemy);
		SpawnEnemy(FPOINT{ float(x), float(y) }, EEnemyType::BeeCopter);
		generateTime = 0.0f;
	}

	// Enemy 업데이트
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
		// 화면 밖으로 벗어나면 제거
		if (IsOutofScreen((*it)->getRect(), 0.0f))
		{
			(*it)->Release();
			delete (*it);
			it = enemys.erase(it);
		}
		else		// 남은 애들은 렌더
		{
			enemy = (*it);
			enemy->Render(hdc);
			it++;
		}
	}
}

// 스폰 시 collision 박스가 창과 충돌하면 사라지므로 주의
void EnemyManager::SpawnEnemy(const FPOINT& pos, EEnemyType enemyType)
{
	Enemy* enemy = CreateEnemy(enemyType);
	if (nullptr != enemy)
	{
		enemy->SetPos(pos);
		enemys.push_back(enemy);
	}
}