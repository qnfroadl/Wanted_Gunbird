#include "Missile.h"
#include "Image.h"
#include "ImageManager.h"
#include "CollisionManager.h"

void Missile::Init()
{
	
}

void Missile::Release()
{
	if (playerAttackDefault)
	{
		playerAttackDefault->Release();
		delete playerAttackDefault;
		playerAttackDefault = nullptr;
	}
	if (playerAttackMissile)
	{
		playerAttackMissile->Release();
		delete playerAttackMissile;
		playerAttackMissile = nullptr;
	}
}

void Missile::Update()
{
}

void Missile::Render(HDC hdc)
{
}
