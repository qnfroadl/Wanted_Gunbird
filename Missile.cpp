#include "Missile.h"
#include "Image.h"
#include "ImageManager.h"
#include "CollisionManager.h"

void Missile::Init()
{
	playerAttackDefault = ImageManager::GetInstance()->AddImage("Player",
		L"assets/Sprites/Characters/tetsu_playerAttackDefault.bmp",
		2, 29, true, RGB(255, 0, 255));
	if (!playerAttackDefault)
		return;
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
	/*if (playerAttackDefault)
	{
		playerAttackDefault->Render(hdc, );
	}*/
}
