#include "Enemy.h"
#include "ImageManager.h"
#include "CommonFunction.h"
#include "Image.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "ActionPattern.h"
#include "MissilePattern.h"
#include "EnemyMissileManager.h"

void Enemy::Init(EEnemyType type, EImageKey key, const wchar_t* filePath, float width, float height,
	int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	this->type = type;
	this->key = key;
	this->AddTag(GameTag::Enemy);

	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height, 
		maxFrameX, maxFrameY, isTransparent, transColor);

	this->width = width / float(maxFrameX);
	this->height = height / float(maxFrameY);

	if (type == EEnemyType::MidBoss)
	{
		actionPattern = new ActionPattern(100.0, 0.0, 500.0);
		actionPattern->setLinearDir();
	}
	if (type == EEnemyType::FlyingEnemy)
	{
		actionPattern = new ActionPattern(0.0, 0.0, 0.0);
		actionPattern->setIsCurve(true);
		float x = rand() % WINSIZE_X;
		actionPattern->pushfront(FPOINT{ x / 2.0f, 200 });
		if (rand() % 2==1)
		{
			actionPattern->setIsCurve(true);
		}
	}
	
	FPOINT startPos = actionPattern->getStartPoint();
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
	pattern->Init(key, pos, fireCount, fireDelay, speed, angleMin, angleMax);
	
	missilePatterns.push_back(pattern);
}

void Enemy::Fire()
{
	if (!missilePatterns.empty())
	{
		FPOINT pos = GetPos();
		MissilePattern* pattern = missilePatterns.front();
		missilePatterns.pop_front();

		// missileManager한테 pos, missile patern넘겨주기
		EnemyMissileManager::GetInstance()->Fire(pos, pattern);
	}
}

void Enemy::Release()
{
	if (actionPattern)
	{
		delete actionPattern;
		actionPattern = nullptr;
	}
	
	CollisionManager::GetInstance()->DeleteCollision(collision);
}

void Enemy::Update()
{
	if (IsActive())
	{		
		FPOINT pos = GetPos();
		
		// update position
		VEC2 step{0.0f, 0.0f};
		if (actionPattern)
		{
			collision->SetRect(GetRectAtCenter(pos.x, pos.y, width, height));
			step = actionPattern->move(collision->GetRect());
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

		// Image마다 fire 주기가 다름
		if (key == EImageKey::MidBossBasic)
		{
			if (fireTime > 1.0f)
			{
				float angle = float(rand() % 120 + 40);
				setMissilePattern(2, 1.0f, 5, angle, angle);
				fireTime = 0.0f;
			}
		}
		if (key == EImageKey::MidBossUpgrade)
		{
			if (fireTime > 0.5f)
			{				
				setMissilePattern(4, 1.0f, 5, 40, 160);
				fireTime = 0.0f;
			}
		}

		Fire();
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

void Enemy::Dead()
{
	collision->SetActive(false);
	collision->SetRect(RECT{ 0,0,0,0 });
	SetActive(false);
}

const RECT& Enemy::getRect()
{
	return collision->GetRect();
}
 
void Enemy::Damaged(int damage)
{
	hp -= damage;

	if (key == EImageKey::MidBossBasic)
	{
		if (hp > 0 && hp < 1000)
		{
			key = EImageKey::MidBossUpgrade;
			image = ImageManager::GetInstance()->FindImage(EImageKey::MidBossUpgrade);
		}
	}
		
	if (hp <= 0)
 	 {
	  	Dead();
	}
 }
