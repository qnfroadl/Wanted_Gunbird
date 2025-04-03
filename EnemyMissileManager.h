#pragma once
#include "config.h"
#include <vector>
#include "GameObject.h"
#include "Singleton.h"
#include <list>
#include "EnemyMissile.h"


class EnemyMissileManager : public Singleton<EnemyMissileManager>
{
private:
	std::list<class EnemyMissile*> listMissiles;
	//std::list<std::unique_ptr< EnemyMissile>> listMissiles;
	std::vector<class EnemyMissile*>::iterator iterMissiles;
	
	std::list<SpawnMissileInfo> listMissileInfo;
	std::unordered_map<EEnemyType, MissileImgInfo> missileImgInfoMap;

	EnemyMissile* CreateMissile(EEnemyType enemyType, SpawnMissileInfo* it);

public:
	EnemyMissileManager();

	virtual ~EnemyMissileManager();
	
	void InitMissile();
	
	void Fire(FPOINT pos, float angle, class MissileType* type);

	void Fire(FPOINT pos, class MissilePattern* pattern);

	void Init();
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

};

