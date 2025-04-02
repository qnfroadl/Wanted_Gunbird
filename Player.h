#pragma once
#include "config.h"
#include "GameActor.h"

class Image;
class PlayerDefaultAttack;
class CollisionRect;
class Player : public GameActor
{
public:
	bool isActive;
	int hp;
	int power;
	int bombCount;
	int animFrame;
	int elapsedFrame;
	int score;
	float speed;
	int attackLevel;
	Image* image;
	PlayerDefaultAttack* missile;
	CollisionRect* playerRect;
	void CollisionDetected(GameObject* obj);
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