#pragma once
#include "Singleton.h"
#include <bitset>
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"
#include <deque>
#include <unordered_map>

class Enemy;
class EnemyManager: public Singleton<EnemyManager>
{
private:
	std::deque<Enemy*> enemys;
	std::unordered_map<EEnemyType, EnemyImgInfo> enemyInfoMap;
	Enemy* CreateEnemy(EEnemyType enemyType);
	float generateTime;

public:
	void InitEnemy();
	bool IsLiveEnmey();

	void Init();

	void Release();		
	void Update();		
	void Render(HDC hdc);

	inline std::deque<class Enemy*> getEnemys() { return enemys; }

	void SpawnEnemy(const FPOINT& pos, EEnemyType enemyType);
};