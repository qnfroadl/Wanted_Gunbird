#pragma once
#include "config.h"
#include "GameActor.h"

class Image;
class MissileManager;
class Player : public GameActor
{
public:
	bool isActive;
	int hp;
	int power;
	int bombCount;
	MissileManager* missileMgr;
	int animFrame;
	int elapsedFrame;
	int score;
	Image* image;
	Image* playerDefaultShotImage;
	Image* playerMissileShotImage;
	float speed;
	int attackLevel;

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