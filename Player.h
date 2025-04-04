#pragma once
#include "config.h"
#include "GameActor.h"

class Image;
class PlayerAttackManager;
class CollisionRect;
class PlayerBomb;
class Player : public GameActor
{
private:
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
	//PlayerDefaultAttack* missile;
	PlayerAttackManager* attackManager;
	CollisionRect* playerCollision;
	// PlayerBomb* playerBomb;
	void CollisionDetected(GameObject* obj);

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move(float degree);
	void Fire();
	void IncreaseAttackLevel();
	void IncreaseBomb();
	void ActivateBomb();

	int GetBombCount();
};