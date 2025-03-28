#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

#include "CollisionManager.h"
#include "NormalBullet.h"
#include "BulletManager.h"
#include "Rocket.h"
#include "ImageManager.h"
#include "TimerManager.h"

void Enemy::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(TEXT("Rocket")))
	{
		if (0 < tags.count(TEXT("NormalBullet")))
		{
			// 로켓이 쏜 총알과 부딪혔따.
			this->SetActive(false);	//Enemy비활성
			obj->SetActive(false);	//Bullet비활성
		}
		else
		{
			//로켓과 부딪혔따.
			this->SetActive(false);	// Enemy비활성
			obj->SetActive(false);	// Rocket 비활성
		}
	}

}
void Enemy::SetActive(bool _bActive)
{
	GameActor::SetActive(_bActive);
	collision->SetActive(_bActive);
}

bool Enemy::IsTargeting()
{
	return nullptr == this->target ? false : true;
}

void Enemy::Init()
{
	this->AddTag(TEXT("Enemy"));

	curAngle = -3.14f / 2;
	bOnceFired = false;
	this->target = nullptr;
	this->SetPos(WINSIZE_X / 2 - 300, 150);
	moveSpeed = 6.f;

	image = ImageManager::GetInstance()->AddImage("Enemy", TEXT("Image/ufo.bmp"), 530, 32, 10, 1, true, RGB(255, 0, 255));
	if (nullptr == image)
	{
		// 잘못된 이미지, 로드실패
		return;
	}

	animFrame = 0;
	elapsedFrame = 0;

	FPOINT pos = this->GetPos();
	RECT rt = { pos.x, pos.y, pos.x + 53, pos.y + 32 };
	collision = CollisionManager::GetInstance()->CreateCollisionRect(this, rt);
	collision->Bind([&](GameObject* obj)
		{
			this->CollisionDetected(obj);
		});

	bulletManager = new BulletManager();
	bulletManager->AddTag(TEXT("Enemy"));
	bulletManager->Init();
}

void Enemy::Release()
{
	// if (nullptr != image)
	// {
	// 	image->Release();
	// 	delete image;
	// 	image = nullptr;
	// }

	CollisionManager::GetInstance()->DeleteCollision(collision);

	if (nullptr != bulletManager)
	{
		bulletManager->Release();
		delete bulletManager;
		bulletManager = nullptr;
	}
}

void Enemy::Update()
{
	if (IsActive())
	{
		FPOINT pos = GetPos();
		collision->SetRect(GetRectAtCenter(pos.x, pos.y, 53, 32));

		this->elapsedFrame++;

		if (5 <= elapsedFrame)
		{
			elapsedFrame = 0;
			animFrame++;
			if (image->GetMaxFrameX() <= animFrame)
			{
				animFrame = 0;
			}
		}

		if (IsTargeting())
		{
			MoveToTarget();
		}
	}

	bulletManager->Update();
}

void Enemy::Render(HDC hdc)
{
	if (this->IsActive())
	{
		const FPOINT& pos = this->GetPos();
		image->FrameRender(hdc, pos.x, pos.y, animFrame, 0, false);
	}

	bulletManager->Render(hdc);
}

void Enemy::MoveToTarget()
{
	if (nullptr != target && target->IsActive())
	{
		
		const FPOINT& pos = this->GetPos();

		float angle = GetAngle(pos, target->GetPos());	// 실제로 적을 향해 꺽여야 하는 방향.
		
		curAngle = curAngle + ((angle - curAngle) * 0.015);	// 보간

		this->AddPos(cosf(curAngle) * moveSpeed, -1 * sinf(curAngle) * moveSpeed);

		float distance = GetDistance(pos, target->GetPos());
		if (false == bOnceFired && distance < 400)
		{
			bOnceFired = true;
			bulletManager->Fire(BulletType::Normal, pos, RAD_TO_DEG(angle), 10.f);
		}

	}
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}
