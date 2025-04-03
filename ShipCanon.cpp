#include "ShipCanon.h"

#include "ShotManager.h"
#include "CollisionManager.h"
#include "CommonFunction.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"

void ShipCanon::On_CollisionDetected(GameObject* obj)
{

}

void ShipCanon::UpdateCanonAngle()
{
	float realAngle = GetAngle(GetPos(), target->GetPos());
	float degAngle = RAD_TO_DEG(realAngle);
	if (degAngle < 0)
	{
		if (degAngle < -140)
		{
			image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_210);
			angle = -160;
		}
		else if (degAngle < -110)
		{
			image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_250);
			angle = -125;
		}
		else if (degAngle < -70)
		{
			image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_270);
			angle = -90;
		}
		else if (degAngle < -30)
		{
			image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_290);
			angle = -65;
		}
		else{
			image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_330);
			angle = -20;
		}
	}

}

void ShipCanon::Init()
{
	this->AddTag(GameTag::Boss_Canon);

	ratio = 1;

	ImageManager::GetInstance()->AddImage(EImageKey::Canon_210,
		L"assets/Sprites/Enemies/Boss/210.bmp", 40 * ratio, 40 * ratio, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::Canon_250,
		L"assets/Sprites/Enemies/Boss/250.bmp", 40 * ratio, 40 * ratio, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::Canon_270,
		L"assets/Sprites/Enemies/Boss/270.bmp", 40 * ratio, 40 * ratio, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::Canon_290,
		L"assets/Sprites/Enemies/Boss/290.bmp", 40 * ratio, 40 * ratio, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::Canon_330,
		L"assets/Sprites/Enemies/Boss/330.bmp", 40 * ratio, 40 * ratio, true, RGB(255, 0, 255));

	target = nullptr;

	image = ImageManager::GetInstance()->FindImage(EImageKey::Canon_270);
	
	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{});
	collision->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj);
		});
	
	elapsedTime = 0.f;
	fireDelay = 1;
}

void ShipCanon::Update()
{
	if (nullptr != target)
	{
		// target과 나 사이의 angle 계산.
		UpdateCanonAngle();
		
		// CollisionUpdate
		collision->SetRect(GetRectAtCenter(GetPos().x, GetPos().y, 40 * ratio, 40 * ratio));

		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (fireDelay < elapsedTime) {
			elapsedTime = 0;
			Fire();
		}
	}
}

void ShipCanon::Render(HDC hdc)
{
	if (nullptr != image)
	{
		image->RenderCenter(hdc, GetPos().x, GetPos().y);
	}
}

void ShipCanon::Release()
{

}

void ShipCanon::SetTarget(GameActor* target)
{
	this->target = target;
}

void ShipCanon::SetActive(bool bActive)
{
	GameActor::SetActive(bActive);
	collision->SetActive(bActive);
}

void ShipCanon::SetFireDelay(float fireDelay)
{
	this->fireDelay = fireDelay;
}

void ShipCanon::Fire()
{
	FPOINT leftPos = GetPos();
	FPOINT rightPos = GetPos();

	leftPos.x += cosf(DEG_TO_RAD(angle - 90)) * 10 * ratio;
	leftPos.y += -sinf(DEG_TO_RAD(angle - 90)) * 10 * ratio;
	leftPos.x += cosf(DEG_TO_RAD(angle)) * 20 * ratio;
	leftPos.y += -sinf(DEG_TO_RAD(angle)) * 20 * ratio;
	
	rightPos.x += cosf(DEG_TO_RAD(angle + 90)) * 10 * ratio;
	rightPos.y += -sinf(DEG_TO_RAD(angle + 90)) * 10 * ratio;
	rightPos.x += cosf(DEG_TO_RAD(angle)) * 20 * ratio;
	rightPos.y += -sinf(DEG_TO_RAD(angle)) * 20 * ratio;

	ShotManager::GetInstance()->Fire(leftPos, angle, 350);
	ShotManager::GetInstance()->Fire(rightPos, angle, 350);

}

void ShipCanon::AddHP(int addHp)
{
	this->hp += addHp;
	if (this->hp <= 0)
	{
		Dead();
	}
}

void ShipCanon::Dead()
{
	SetActive(false);
}
