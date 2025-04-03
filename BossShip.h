#pragma once

#include "GameActor.h"
#include <array>

class Image;
class ShipCannon;
class BossShip : public GameActor
{
private:
	Image* baseImage;	//	
	Image* baseDestroyLeft;
	Image* baseDestroyRight;
	GameActor* target;
	int width;
	int height;

	array<ShipCannon*, 8> aryCannons;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void SetTarget(GameActor* target);

	void AddMove(const FPOINT& movePos);
	void CannonPosUpdate();
};

