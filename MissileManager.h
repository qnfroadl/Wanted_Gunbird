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
	void Release() override;		// 메모리 해제
	void Update() override;		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc) override;	// 프레임 단위로 출력(이미지, 텍스트 등)
};

