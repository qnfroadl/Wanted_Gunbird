#pragma once
#include "GameActor.h"
#include <vector>
#define AMMUNITION 100

class PlayerDefaultAttack;
class PlayerMissileAttack;
class PlayerAttackManager : GameObject
{
private:
	PlayerDefaultAttack* defaultAttack;
	vector<PlayerDefaultAttack*> defaultAttackVec;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, int level);
};

