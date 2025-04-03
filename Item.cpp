#include "Item.h"

#include "CollisionManager.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "config.h"

//test
#include "EffectManager.h"

#define LT 135
#define RT 45
#define LB 225
#define RB 315

Item::Item(ItemType type, int lifeTime)
{
	SetItemType(type);
	SetLifeTime(lifeTime);
}

Item::~Item()
{

}

void Item::Init()
{
	angle = RT;
	speed = 300;
	curFrame = 0;

	if (ItemType::BombAdd == this->type)
	{
		this->image = ImageManager::GetInstance()->AddImage(EImageKey::PickupBomb, TEXT("assets/Sprites/Misc/pickup_bomb.bmp"), 216, 16, 8, 1, true, RGB(255, 0, 255));
		width = 27; // 216 / 8;
		height = 16;
	}
	else 
	{
		// 파워업으로 변경 필요.
		this->image = ImageManager::GetInstance()->AddImage(EImageKey::PickupPower, TEXT("assets/Sprites/Misc/puckup_power.bmp"), 418, 13, 19, 1, true, RGB(255, 0, 255));
		width = 27; //418 / 19;
		height = 13;
	}
	
	if (nullptr == image)
	{
		MessageBox(NULL, TEXT("item not loaded"), NULL,NULL);
	}

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{-100,-100, -100,-100});
	collision->Bind([&](GameObject* obj)
		{
			this->On_CollisionDetected(obj);
		});
}

void Item::Update()
{
	if (IsActive())
	{
		curFrame++;
		if (image->GetMaxFrameX() <= curFrame/4)
		{
			curFrame = 0;
		}

		this->lifeTime -= TimerManager::GetInstance()->GetDeltaTime();

		MoveInWindow();

		// LifeTime을 점점 깍다가, 시간이 n초 이하가 되면 깜빡이게 만든다. to do, 일단은 바로 없애버려
		if (lifeTime < 0)
		{
			SetActive(false);
			collision->SetActive(false);
		}
	}
}

void Item::Render(HDC hdc)
{
	FPOINT pos = GetPos();
	
	image->FrameRender(hdc, pos.x, pos.y, curFrame/4, 0);

}

void Item::Release()
{
	CollisionManager::GetInstance()->DeleteCollision(this->collision);
}

void Item::On_CollisionDetected(GameObject* obj)
{
	if (obj->FindTag(GameTag::Player))
	{
		SetActive(false);
		collision->SetActive(false);
	}
}

void Item::MoveInWindow()
{
	FPOINT pos = GetPos();
	
	if (RectInRect(collision->GetRect(), RECT{ 0,0, 3, WINSIZE_Y }))
	{	// 왼쪽 벽
		angle = (angle == LT)? RT : RB;
	}
	else if(RectInRect(collision->GetRect(), RECT{ 0,0, WINSIZE_X, 3 }))
	{	// 상단
		angle = (angle == LT) ? LB : RB;

	}
	else if (RectInRect(collision->GetRect(), RECT{ WINSIZE_X - 3,0, WINSIZE_X, WINSIZE_Y }))
	{	//오른쪽 벽
		angle = (angle == RT) ? LT : LB;

	}
	else if (RectInRect(collision->GetRect(), RECT{ 0,WINSIZE_Y - 3, WINSIZE_X, WINSIZE_Y }))
	{	// 하단
		angle = (angle == LB) ? LT : RT;

	}
	
	pos.x += TimerManager::GetInstance()->GetDeltaTime() * speed * cosf(DEG_TO_RAD(angle));
	pos.y += TimerManager::GetInstance()->GetDeltaTime()  * -speed * sinf(DEG_TO_RAD(angle));

	SetPos(pos);
	collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));
	
}

void Item::SetLifeTime(int lifeTime)
{
	this->lifeTime = lifeTime;
}

void Item::SetItemType(ItemType type)
{
	this->type = type;
	this->AddTag(type == ItemType::BombAdd ? GameTag::BombUp : GameTag::PowerUp);
}

