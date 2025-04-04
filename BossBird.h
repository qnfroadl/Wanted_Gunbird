#pragma once

#include "GameActor.h"
#include <array>

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
	CollisionRect* right;
	array<FPOINT, 5> leftAttackPos;
	
	int leftHP;
	int rightHP;
	int step;
	int attackStep;
	int curFrame;
	int speed;
	float moveAngle;
	int width;
	int height;
	float propellerTime;
	float elapsedTime;
	float attackDelay;
	void Appear();
	void Fight();
	void Destroyed();
	void DestroyedEffect(float dx, float dy, EEffectType type);
	void Disappear();
	
	bool Move(const FPOINT& destPos);	//목적지까지 이동 됐다면 true, 아니면 false반환.

	void Damaged(int& hp, int damage);

	void On_CollisionDetected(GameObject* obj, int& hp);

	void UpdateCollisionRect();
	
	void Attack();
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetTarget(GameActor* target);
};

