#include "BossShip.h"

#include "ImageManager.h"
#include "Image.h"
#include "ShipCanon.h"
void BossShip::Init()
{
	this->width = 193;
	this->height = 441;

	baseImage = ImageManager::GetInstance()->AddImage(EImageKey::ShipBase,
		L"assets/Sprites/Enemies/Boss/Base.bmp", width, height, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyedLeft,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed_Left.bmp", 65, 120, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyedRight,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed_Right.bmp", 64, 120, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyed,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed.bmp", width, height, true, RGB(255, 0, 255));
	
	baseDestroyLeft = nullptr;
	baseDestroyRight = nullptr;

	for (int i = 0; i < 8; i++)
	{
		aryCanons[i] = new ShipCanon();
		aryCanons[i]->Init();
	}

}

void BossShip::Update()
{

}

void BossShip::Render(HDC hdc)
{
	baseImage->Render(hdc, width, height);
}

void BossShip::Release()
{

}

void BossShip::AddMove(const FPOINT& movePos)
{

}
