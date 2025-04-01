#pragma once
#include "GameActor.h"
#include <unordered_set>

class Image;
class CollisionRect;
class BulletManager;
class SampleEnemy : public GameActor	
{
private:
	GameActor* target;
	float curAngle;
	float moveSpeed;
	Image* image;
	int animFrame;
	int elapsedFrame;
	bool bOnceFired;

	CollisionRect* collision;
	BulletManager* bulletManager;

	void CollisionDetected(GameObject* obj);
public:
	void Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void MoveToTarget();

	SampleEnemy();
	~SampleEnemy();

	void SetActive(bool _bActive);

	void Kamikaze(GameActor* target) { this->target = target; }	// ÀÚÆø ¸í·É
	bool IsTargeting();

};

