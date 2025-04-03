#include "EnemyMissile.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "MissilePattern.h"


EnemyMissile::EnemyMissile(float speed, float angle)
{
	this->speed = speed;
	this->angle = angle;

	image = nullptr;
	damage = 1;
	width = 0.0f;
	height = 0.0f;
	elapsedTime = 0.0f;
	collision = nullptr;
	animFrame = 0;
}

EnemyMissile::~EnemyMissile()
{
	// 에러 나는 이유
	//if (image)
	//{
	//	image->Release();
	//	delete image;
	//	image = nullptr;
	//}
}

void EnemyMissile::Init(EImageKey key, const wchar_t* filePath, FPOINT startingPos, float width,
	float height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	this->width = width / (float)maxFrameX;
	this->height= height / (float)maxFrameY;

	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height,
		maxFrameX, maxFrameY, isTransparent, transColor);
	
	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{});	
	collision->Bind([&](GameObject* obj)
		{
			this->On_CollisionDetected(obj);
		});

	SetPos(startingPos);
}

void EnemyMissile::Release()
{
	CollisionManager::GetInstance()->DeleteCollision(collision);
}

void EnemyMissile::Update()
{
	if (IsActive())
	{
		FPOINT pos = GetPos();
		
		// collision 설정
		collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));						

		pos.x += speed * cosf(DEG_TO_RAD(angle));
		pos.y += speed * sinf(DEG_TO_RAD(angle));
		SetPos(pos);

		// animation
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedTime > 0.1f)
		{
			animFrame++;
			if (animFrame >= image->GetMaxFrameX())
			{
				animFrame = 0;
			}
			elapsedTime = 0.0f;
		}
	}
}

void EnemyMissile::Render(HDC hdc)
{
	if (this->IsActive())
	{
		const FPOINT& pos = this->GetPos();
		image->FrameRender(hdc, pos.x, pos.y, animFrame, 0, false);
	}
}

const RECT& EnemyMissile::getRect()
{
	return collision->GetRect();
}

void EnemyMissile::On_CollisionDetected(GameObject* obj)
{
	//auto tags = obj->GetTags();
	//if (0 < tags.count(GameTag::Player))
	//{
	//	obj->SetActive(false);
	//	this->SetActive(false);
	//}
}
