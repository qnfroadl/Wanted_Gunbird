#pragma once
#include "GameActor.h"
#include <vector>
#define AMMUNITION 30

class PlayerDefaultAttack;
class PlayerMissileAttack;
class PlayerAttackManager : public GameObject
{
private:
	vector<PlayerDefaultAttack*> defaultAttackVec;
	vector<PlayerMissileAttack*> missileAttackVec;

	void Fire(const FPOINT& pos, int level, vector<PlayerDefaultAttack*>& attack);
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, int level);
};

