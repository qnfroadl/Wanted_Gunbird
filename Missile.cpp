#include "Missile.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "MissilePattern.h"


Missile::Missile()
{
	image = nullptr;
	damage = 1;
	speed = 5.0f;
	collision = nullptr;
	animFrame = 0;
}

Missile::~Missile()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Missile::Init(const string& key, const wchar_t* filePath, float width, float height,
	int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height,
		maxFrameX, maxFrameY, isTransparent, transColor);

	pattern = new MissilePattern;

	FPOINT startPoint = pattern->getStartPoint();
	SetPos(startPoint);

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{});
	collision->Bind([&](GameObject* obj)
		{
			this->On_CollisionDetected(obj);
		});
}

void Missile::Release()
{
	if (pattern)
	{
		delete pattern;
		pattern = nullptr;
	}
}

void Missile::Update()
{
}

void Missile::Render(HDC hdc)
{
	if (this->IsActive())
	{
		const FPOINT& pos = this->GetPos();
		image->FrameRender(hdc, pos.x, pos.y, animFrame, 0, false);
	}
}

void Missile::On_CollisionDetected(GameObject* obj)
{
}
