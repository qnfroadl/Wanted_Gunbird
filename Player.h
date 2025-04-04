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
	int life;
	int power;
	int bombCount;
	int animFrame;
	float elapsedFrame;
	int score;
	float speed;
	int attackLevel;
	bool bRightMove;
	bool bLeftMove;
	float respawnTime;
	bool bIsDead;
	Image* image;
	Image* leftMoveImage;
	Image* rightMoveImage;
	//PlayerDefaultAttack* missile;
	PlayerAttackManager* attackManager;
	CollisionRect* playerCollision;
	PlayerBomb* playerBomb;
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
	void Dead();
	void Respawn();
};