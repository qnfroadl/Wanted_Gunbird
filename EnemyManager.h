#pragma once

#include <bitset>
#include "config.h"
#include "Singleton.h"
#include "GameObject.h"
#include <deque>


class EnemyManager: public GameObject
{
private:
	std::deque<class Enemy*> enemys;

public:
	bool IsOutofScreen();

	bool IsLiveEnmey();

	void Init() override;
	void Release() override;		// 메모리 해제
	void Update() override;		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc) override;	// 프레임 단위로 출력(이미지, 텍스트 등)

	inline std::deque<class Enemy*> getEnemys() { return enemys; }
};