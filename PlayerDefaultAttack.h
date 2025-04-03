#pragma once
#include "GameActor.h"

class Image;
class CollisionRect;

class PlayerDefaultAttack : public GameActor
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

	void Fire(FPOINT pos);
	void Fire(int posX, int posY);
	void Move();

	void SetActive(bool bActive) override;
};

