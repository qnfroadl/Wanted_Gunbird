#pragma once
#include "config.h"
#include "GameActor.h"

class CollisionManager;
class Image;
class MissileManager;
class Player : public GameActor
{
public:
	bool isActive;
	FPOINT pos;
	int hp;
	int power;
	int bombCount;
	MissileManager* missileMgr;
	int score;
	Image* image;
	float speed;
	CollisionManager* collision;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move(float degree);
	void Fire();
};