#pragma once
#include "Singleton.h"
#include <bitset>
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"
#include <deque>


class EnemyManager : public Singleton<EnemyManager>
{
private:
	std::deque<class Enemy*> enemys;

public:
	bool IsOutofScreen();

	bool IsLiveEnmey();

	void Init();
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)

	inline std::deque<class Enemy*> getEnemys() { return enemys; }
};