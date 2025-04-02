#pragma once
#include "GameActor.h"

class Image;
class CollisionRect;

class PlayerDefaultAttack : GameActor
{
private:
	float speed;
	float angle;
	Image* playerAttackDefault;
	CollisionRect* attackDefaultCollision;
	void CollisionDetected(GameObject* obj);
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT pos, int level);
	void Move();
};

