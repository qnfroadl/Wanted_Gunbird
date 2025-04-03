#pragma once

#include "GameActor.h"
#include <array>

class Image;
class ShipCanon;
class BossShip : public GameActor
{
private:
	Image* baseImage;	//	
	Image* baseDestroyLeft;
	Image* baseDestroyRight;

	int width;
	int height;

	array<ShipCanon*, 8> aryCanons;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AddMove(const FPOINT& movePos);

};

