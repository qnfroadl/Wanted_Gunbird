#pragma once
#include "GameActor.h"

class Image;
class CollisionManager;
class Missile : GameActor
{
private:
	Image* playerAttackDefault;
	Image* playerAttackMissile;
	float speed;
	CollisionManager* projectileCollision;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);


};

