#include "Enemy.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "ActionPattern.h"


void Enemy::Init(const string& key, const wchar_t* filePath, float width, float height,
	int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height, 
		maxFrameX, maxFrameY, isTransparent, transColor);
	if (nullptr == image)
	{		
		return;
	}

	FPOINT pos = this->GetPos();
	RECT rt = { pos.x, pos.y, pos.x + width, pos.y + height };
	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, rt);
	collision->Bind([&](GameObject* obj)
		{
			
		});

}

void Enemy::Update()
{
	if (IsActive())
	{		
		FPOINT pos = GetPos();
		
		// update position
		getPattern()->move();

		//update animation frame
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

void Enemy::Render(HDC hdc)
{
	if (this->IsActive())
	{
		const FPOINT& pos = this->GetPos();
		image->FrameRender(hdc, pos.x, pos.y, animFrame, 0, false);
	}
}
