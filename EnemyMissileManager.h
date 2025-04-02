#pragma once
#include "config.h"
#include <vector>
#include "GameObject.h"

class EnemyMissileManager : public GameObject
{
private:
	vector<class EnemyMissile*> vecMissiles;
	vector<EnemyMissile*>::iterator iterMissiles;

public:
	EnemyMissileManager();

	virtual ~EnemyMissileManager();
	
	void Fire(FPOINT pos, float angle, class MissileType* type);

	void Fire(FPOINT pos, class MissilePattern* pattern);

	void Init() override;
	void Release() override;		// �޸� ����
	void Update() override;		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc) override;	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)
};

