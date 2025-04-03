#pragma once

#include "GameActor.h"

class Image;
class CollisionRect;
class ShipCanon : public GameActor
{

private:
	Image* image;
	int ratio;
	float angle;
	CollisionRect* collision;
	float elapsedTime;
	GameActor* target;	// 타겟을 계속 바라볼 것.
	float fireDelay;
	int hp;

	void On_CollisionDetected(GameObject* obj);
	void UpdateCanonAngle();

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void SetTarget(GameActor* target);
	void SetActive(bool bActive) override;
	void SetFireDelay(float fireDleay);
	void Fire();
	void AddHP(int addHp);
	void Dead();
};

