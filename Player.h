#pragma once
#include "config.h"
#include "GameActor.h"

class CollisionManager;
class Image;
class MissileManager;
class Player : public GameActor
{
public:
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
	void Move(float degree);
	
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};