#include "Item.h"

#include "CollisionManager.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "config.h"

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
		this->image = ImageManager::GetInstance()->AddImage("PickupBomb", TEXT("assets/Sprites/Misc/pickup_bomb.bmp"), 216, 16, 8, 1, true, RGB(255, 0, 255));
		width = 27; // 216 / 8;
		height = 16;
	}
	else 
	{
		// 파워업으로 변경 필요.
		this->image = ImageManager::GetInstance()->AddImage("PickupBomb", TEXT("assets/Sprites/Misc/pickup_bomb.bmp"), 216, 16, 8, 1, true, RGB(255, 0, 255));
		width = 27; //216 / 8;
		height = 16;
	}
	
	if (nullptr == image)
	{
		MessageBox(NULL, TEXT("pickup_bomb not loaded"), NULL,NULL);
	}

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{-100,-100, -80,-80});
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

		// LifeTime을 점점 깍다가, 시간이 n초 이하가 되면 깜빡이게 만든다. to do

		MoveInWindow();
	}
	
}

void Item::Render(HDC hdc)
{
	FPOINT pos = GetPos();
	if (8*4 <= curFrame)
	{
		curFrame = 0;
	}
	image->FrameRender(hdc, pos.x, pos.y, curFrame/4, 0);

}

void Item::Release()
{
	CollisionManager::GetInstance()->DeleteCollision(this->collision);
}

void Item::On_CollisionDetected(GameObject* obj)
{
	
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

