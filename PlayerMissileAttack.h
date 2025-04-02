#pragma once
#include "GameActor.h"

class Image;
class CollisionRect;

class PlayerMissileAttack : GameActor
{
private:
	float missileElapsedFrame;
	int missileAnimFrame;
	float speed;
	float angle;\
	Image* playerAttackMissile;
	CollisionRect* attackMissileCollision;
	void CollisionDetected(GameObject* obj);
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, int level);
	void Move();
};

