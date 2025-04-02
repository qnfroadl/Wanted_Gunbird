#pragma once
#include "Singleton.h"
#include <bitset>
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"
#include <deque>


class Enemy;
class EnemyManager: public Singleton<EnemyManager>
{
private:
	std::deque<Enemy*> enemys;

	Enemy* CreateEnemy(int enemytType);

public:
	bool IsLiveEnmey();

	void Init();

	void Release();		
	void Update();		
	void Render(HDC hdc);

	inline std::deque<class Enemy*> getEnemys() { return enemys; }

	void SpawnEnemy(const FPOINT& pos, int enemyType);
};