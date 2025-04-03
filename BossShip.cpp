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
		aryCannons[i] = new ShipCannon();
		aryCannons[i]->Init();
	}
	
}

void BossShip::Update()
{
	CannonPosUpdate();
	for (int i = 0; i < 8; i++)
	{
		if (aryCannons[i]->IsActive())
		{
			aryCannons[i]->Update();
		}
	}
}

void BossShip::Render(HDC hdc)
{
	baseImage->RenderCenter(hdc, GetPos().x, GetPos().y);

	for (int i = 0; i < 8; i++)
	{
		if (aryCannons[i]->IsActive())
		{
			aryCannons[i]->Render(hdc);
		}
	}
}

void BossShip::Release()
{
	for (int i = 0; i < 8; i++)
	{
		aryCannons[i]->Release();	
	}
}

void BossShip::SetTarget(GameActor* target)
{
	for (int i = 0; i < 8; i++)
	{
		aryCannons[i]->SetTarget(target);
	}
}

void BossShip::AddMove(const FPOINT& movePos)
{
	
}

void BossShip::CannonPosUpdate()
{
	FPOINT pos = GetPos();
	for (int i = 0; i < 2; i++)
	{
		aryCannons[0 + (4 * i)]->SetPos(pos.x - 70 * (1 - i * 2), pos.y - 50);
		aryCannons[1 + (4 * i)]->SetPos(pos.x - 76 * (1 - i * 2), pos.y + 61);
		aryCannons[2 + (4 * i)]->SetPos(pos.x - 45 * (1 - i * 2), pos.y + 88);
		aryCannons[3 + (4 * i)]->SetPos(pos.x - 35 * (1 - i * 2), pos.y + 169);
	}
}
