#include "Item.h"

#include "CollisionManager.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TimerManager.h"

Item::Item(ItemType type)
{
	this->type = type;
}

Item::~Item()
{

}

void Item::Init()
{
	angle = 135.f;
	speed = 7;
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

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{});
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
	
	if (IsOutofScreen(collision->GetRect(), 30))
	{
		angle += 90;
		if (360 < angle)
		{
			angle = angle - 360;
		}
	}

	pos.x += speed * cosf(DEG_TO_RAD(angle));
	pos.y += -speed * sinf(DEG_TO_RAD(angle));


	SetPos(pos);
	collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));

	
}

