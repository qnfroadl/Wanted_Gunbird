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
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)
};

