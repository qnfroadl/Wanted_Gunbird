#pragma once
#include "config.h"
#include <vector>
#include "GameObject.h"
#include "Singleton.h"
#include <list>

class EnemyMissileManager : public Singleton<EnemyMissileManager>
{
private:
	vector<class EnemyMissile*> vecMissiles;
	vector<class EnemyMissile*>::iterator iterMissiles;
	
	std::list<MissileInfo> vecMissileInfo;

public:
	EnemyMissileManager();

	virtual ~EnemyMissileManager();
	
	void Fire(FPOINT pos, float angle, class MissileType* type);

	void Fire(FPOINT pos, class MissilePattern* pattern);

	void Init();
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)
};

