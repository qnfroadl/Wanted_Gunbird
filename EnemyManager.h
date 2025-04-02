#pragma once

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

public:
	bool IsLiveEnmey();

	void Init();
	void Release();		
	void Update();		
	void Render(HDC hdc);

	inline std::deque<class Enemy*> getEnemys() { return enemys; }
};