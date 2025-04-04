#pragma once

#include "GameActor.h"
#include <array>

class Image;
class ShipCannon;
class BossShip : public GameActor
{
private:
	enum class State {
		Begin, Fight, Destroyed, Disappear, End
	};
	State state;
	Image* baseImage;	//	
	GameActor* target;
	int speed;
	float moveAngle;
	int width;
	int height;
	bool bCannonsLive;
	int step;
	float elapsedTime;

	array<ShipCannon*, 8> aryCannons;

	void Appear();
	void MoveMove();
	void Destroyed();
	void DestroyedEffect(float dx, float dy, EEffectType type);
	void Disappear();

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetTarget(GameActor* target);

	void Move(const FPOINT& movePos);
	void CannonPosUpdate();
};

