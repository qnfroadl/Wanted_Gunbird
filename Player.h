#pragma once
#include "config.h"
#include "GameActor.h"

class CollisionManager;
class Image;
class EnemyMissileManager;
class Player : public GameActor
{
public:
	bool isActive;
	int hp;
	int power;
	int bombCount;
	EnemyMissileManager* missileMgr;
	int animFrame;
	int elapsedFrame;
	int score;
	Image* image;
	float speed;
	int attackLevel;
	CollisionManager* collision;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move(float degree);
	void Fire();
	void IncreaseAttackLevel();
	void ActivateBomb();
};