#pragma once

#include "GameActor.h"

class Image;
class CollisionRect;
class BossBird : public GameActor
{
private:
	enum class State {
		Begin, Fight, Destroyed, Disappear, End
	};
	State state;
	Image* baseImage;	//	
	Image* propellerImage;
	GameActor* target;

	CollisionRect* left;
	CollisionRect* body;
	CollisionRect* right;

	int leftHP;
	int rightHP;
	int bodyHP;

	int curFrame;
	int speed;
	float moveAngle;
	int width;
	int height;
	float propellerTime;
	float elapsedTime;

	void Appear();
	void MoveMove();
	void Destroyed();
	void DestroyedEffect(float dx, float dy, EEffectType type);
	void Disappear();

	void Damaged(int& hp, int damage);

	void On_CollisionDetected(GameObject* obj, int& hp);

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetTarget(GameActor* target);
};

