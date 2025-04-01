#pragma once
#include "config.h"
#include <vector>
#include "GameObject.h"

class MissileManager : public GameObject
{
private:
	vector<class Missile*> vecMissiles;
	vector<Missile*>::iterator iterMissiles;

public:
	MissileManager();

	virtual ~MissileManager();
	
	void Fire(FPOINT pos, float angle, class MissileType* type);

	void Fire(FPOINT pos, class MissilePattern* pattern);

	void Init() override;
	void Release() override;		// �޸� ����
	void Update() override;		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc) override;	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)
};

