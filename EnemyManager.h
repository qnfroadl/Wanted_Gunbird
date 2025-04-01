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
	void Release() override;		// �޸� ����
	void Update() override;		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc) override;	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	inline std::deque<class Enemy*> getEnemys() { return enemys; }
};