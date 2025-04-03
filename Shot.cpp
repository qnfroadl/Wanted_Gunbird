#include "Shot.h"

#include "ImageManager.h"
#include "Image.h"
#include "CollisionManager.h"
#include "TimerManager.h"
#include "CommonFunction.h"
#include "EffectManager.h"

void Shot::Move()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	FPOINT pos = GetPos();
	pos.x += deltaTime * speed * cosf(DEG_TO_RAD(angle));
	pos.y += deltaTime * speed * -sinf(DEG_TO_RAD(angle));
	SetPos(pos);
	collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));

}

void Shot::On_CollisionDetected(GameObject* obj)
{
	if (obj->FindTag(GameTag::Player))
	{
		// 충 돌 처 리

		this->SetActive(false);
		EffectManager::GetInstance()->PlayEffect(GetPos(), EEffectType::ExplosionNormal);
	}
}

void Shot::Init()
{
	ratio = 2.0;
	shotImage = ImageManager::GetInstance()->AddImage(EImageKey::CanonShot, 
	L"assets/Sprites/Misc/shot.bmp",70 * ratio,7 * ratio,10,1,true, RGB(255,0,255));

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{0,0,0,0});
	collision->Bind([&](GameObject* obj)
		{
			this->On_CollisionDetected(obj);
		});

	speed = 10;
	angle = 0;
	curFrame = 0;
}

void Shot::Update()
{
	if (IsActive())
	{
		// 프레임 기반 X -> 시간 기반이 옳다.

		curFrame++;
		if (this->shotImage->GetMaxFrameX() <= curFrame / 2)
		{
			curFrame = 0;
		}

		Move();
	}
}

void Shot::Render(HDC hdc)
{
	if (IsActive())
	{
		this->shotImage->FrameRender(hdc, GetPos().x, GetPos().y, curFrame/2, 0);
	}
}

void Shot::Release()
{
	CollisionManager::GetInstance()->DeleteCollision(collision);
}

void Shot::Fire(const FPOINT& pos, float angle)
{
	this->SetPos(pos);
	this->angle = angle;

	SetActive(true);
}

void Shot::SetActive(bool bActive)
{
	GameActor::SetActive(bActive);
	collision->SetActive(bActive);
}

void Shot::SetShotImage(EImageKey key, const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	shotImage = ImageManager::GetInstance()->AddImage(key,filePath, width, height, maxFrameX, maxFrameY, isTransparent, transColor);

	this->width = (width / maxFrameX) * ratio;
	this->height = (height / maxFrameY) * ratio;
}

void Shot::SetSpeed(float speed)
{
	this->speed = speed;
}
