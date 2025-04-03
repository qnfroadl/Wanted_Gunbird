#pragma once
#include "GameActor.h"

class Image;
class CollisionRect;

class PlayerBomb : public GameActor
{
private:
	int animFrame;
	int elapsedFrame;
	FPOINT pos;
	Image* bombImage;
	void CollisionDetected(GameObject* obj);
	CollisionRect* bombCollision;

public:
	void Init(FPOINT playerPos);
	void Release();
	void Render(HDC hdc);
	void Update(FPOINT playerPos);

	void BombActivate(FPOINT pos);
};

