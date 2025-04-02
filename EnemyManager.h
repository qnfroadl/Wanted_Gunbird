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
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	inline std::deque<class Enemy*> getEnemys() { return enemys; }
};