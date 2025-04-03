#pragma once
#include "GameActor.h"

class Image;
class CollisionRect;

class PlayerBomb : public GameActor
{
private:
	int animFrame;
	float elapsedFrame;
	FPOINT pos;
	Image* bombImage;
	void CollisionDetected(GameObject* obj);
	int damage;
	CollisionRect* bombCollision;
	FPOINT renderPos;
public:
	void Init(FPOINT playerPos);
	void Release();
	void Render(HDC hdc, FPOINT playerPos);
	void Update();

	void BombActivate(FPOINT pos);
};

