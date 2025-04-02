#include "Enemy.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "ActionPattern.h"
#include "MissilePattern.h"
#include "EnemyMissileManager.h"

void Enemy::Init(const string& key, const wchar_t* filePath, float width, float height,
	int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height, 
		maxFrameX, maxFrameY, isTransparent, transColor);

	this->width = width;
	this->height = height;

	pattern = new ActionPattern(100.0, 100.0, 500.0);
	
	FPOINT startPos = pattern->getStartPoint();
	SetPos(startPos);

	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, RECT{});
	collision->Bind([&](GameObject* obj)
		{
			this->On_CollisionDetected(obj);
		});	
}

void Enemy::setMissilePattern(int fireCount, float fireDelay, float speed, float angleMin, float angleMax)
{
	MissilePattern* pattern = new MissilePattern();
	FPOINT pos = GetPos();
	pattern->Init(pos, fireCount, fireDelay, speed, angleMin, angleMax);
	
	missilePatterns.push_back(pattern);
}

void Enemy::Fire()
{
	if (!missilePatterns.empty())
	{
		MissilePattern* pattern = missilePatterns.front();
		missilePatterns.pop_front();

		// missileManager한테 넘겨주기
		FPOINT pos = GetPos();
		EnemyMissileManager::GetInstance()->Fire(pos, pattern);
	}
}



void Enemy::Release()
{
	if (pattern)
	{
		delete pattern;
		pattern = nullptr;
	}
}

void Enemy::Update()
{
	if (IsActive())
	{		
		FPOINT pos = GetPos();
		
		// update position
		VEC2 step{0.0f, 0.0f};
		if (pattern)
		{
			collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));
			step = pattern->move(collision->GetRect());
		}

		pos.x += step.x;
		pos.y += step.y;
		SetPos(pos);

		//update animation frame
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		fireTime += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedTime > 0.1f)
		{
			animFrame++;
			if (animFrame >= image->GetMaxFrameX())
			{
				animFrame = 0;
			}
			elapsedTime = 0.0f;
		}

		if (fireTime > 3.0f)
		{
			if (rand() % 2)
				setMissilePattern(4, 0.1f, 5, 90.0f, 90.0f);
			else
				setMissilePattern(4, 0.1f, 5, 120.0f, 120.0f);
			Fire();
			fireTime = 0.0f;
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

void Enemy::On_CollisionDetected(GameObject* obj)
{
}
