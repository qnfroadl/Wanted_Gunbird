#include "PlayerMissileAttack.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "GameActor.h"
#include "Enemy.h"
#include "CommonFunction.h"

void PlayerMissileAttack::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(GameTag::Enemy))
	{
		Enemy* enemy = static_cast<Enemy*>(obj);
		enemy->Damaged(10);

		this->SetActive(false);
		this->attackMissileCollision->SetActive(false);
	}
}

void PlayerMissileAttack::Init()
{
	this->AddTag(GameTag::PlayerMissileAttack);
	missileElapsedFrame = 0.0f;
	missileAnimFrame = 0;
	speed = 2000;
	angle = 0;

	playerAttackMissile = ImageManager::GetInstance()->AddImage(EImageKey::PlayerAttackMissile,
		L"assets/Sprites/Characters/tetsu_playerAttackMissile.bmp",
		40, 24, 8, 1, true, RGB(255, 0, 255));
	if (!playerAttackMissile)
		return;

	FPOINT pos = GetPos();
	RECT defaultRect = { pos.x, pos.y, pos.x+2, pos.y+29 };
	attackMissileCollision = CollisionManager::GetInstance()->CreateCollisionRect(this, defaultRect);
	attackMissileCollision->Bind([&](GameObject* obj)
		{
			this->CollisionDetected(obj);
		});
	SetActive(false);
}

void PlayerMissileAttack::Release()
{
	if (playerAttackMissile)
	{
		playerAttackMissile->Release();
		delete playerAttackMissile;
		playerAttackMissile = nullptr;
	}
}

void PlayerMissileAttack::Update()
{
	Move();
	if (IsActive())
	{
		missileElapsedFrame += TimerManager::GetInstance()->GetDeltaTime();
		if (missileElapsedFrame > 0.1f)
		{
			missileAnimFrame++;
			if (missileAnimFrame >= playerAttackMissile->GetMaxFrameX())
			{
				missileAnimFrame = 0;
			}
			missileElapsedFrame = 0.0f;
		}
	}
	if (IsOutofScreen(GetPos()))
	{
		SetActive(false);
		attackMissileCollision->SetActive(false);
	}
}

void PlayerMissileAttack::Render(HDC hdc)
{
	if (IsActive())
	{
		if (playerAttackMissile)
		{
			playerAttackMissile->FrameRender(hdc, GetPos().x, GetPos().y, missileAnimFrame, 0, false);
		}
	}
}

void PlayerMissileAttack::Fire(FPOINT pos, int level)
{
	SetPos(pos);
	if(!IsActive())
	{
		SetActive(true);
		attackMissileCollision->SetActive(true);
		missileAnimFrame = 0;
	}
}

void PlayerMissileAttack::Move()
{
	FPOINT position = GetPos();
	position.x += speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(-90));
	position.y += speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(-90));
	SetPos(position);
	attackMissileCollision->SetRect(GetRectAtCenter(position.x, position.y, 40, 24));
}
