#include "PlayerDefaultAttack.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "GameActor.h"

void PlayerDefaultAttack::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(GameTag::PlayerDefaultAttack))
	{
		if (0 < tags.count(GameTag::Enemy))
		{
			// ·ÎÄÏÀÌ ½ð ÃÑ¾Ë°ú ºÎµúÇûµû.
			this->SetActive(false);	//EnemyºñÈ°¼º
			obj->SetActive(false);	//BulletºñÈ°¼º
		}
		else
		{
			//·ÎÄÏ°ú ºÎµúÇûµû.
			this->SetActive(false);	// EnemyºñÈ°¼º
			obj->SetActive(false);	// Rocket ºñÈ°¼º
		}
	}
}

void PlayerDefaultAttack::Init()
{
	speed = 100;
	angle = 0;
	playerAttackDefault = ImageManager::GetInstance()->AddImage(EImageKey::PlayerAttackDefault,
		L"assets/Sprites/Characters/tetsu_playerAttackDefault.bmp",
		2, 29, true, RGB(255, 0, 255));
	if (!playerAttackDefault)
		return;

	FPOINT pos = GetPos();
	RECT defaultRect = { pos.x, pos.y, pos.x + 2, pos.y + 29 };
	attackDefaultCollision = CollisionManager::GetInstance()->CreateCollisionRect(this, defaultRect);
	attackDefaultCollision->Bind([&](GameObject* obj)
		{
			this->CollisionDetected(obj);
		});	SetActive(false);
}

void PlayerDefaultAttack::Release()
{
	if (playerAttackDefault)
	{
		playerAttackDefault->Release();
		delete playerAttackDefault;
		playerAttackDefault = nullptr;
	}
}

void PlayerDefaultAttack::Update()
{
	if(IsActive())
		Move();
}

void PlayerDefaultAttack::Render(HDC hdc)
{
	if (IsActive())
	{
		if (playerAttackDefault)
		{
			playerAttackDefault->Render(hdc, GetPos().x, GetPos().y);
		}
	}

}

void PlayerDefaultAttack::Fire(FPOINT pos, int level)
{
	SetPos(pos);
	SetActive(true);
}

void PlayerDefaultAttack::Move()
{
	FPOINT position = GetPos();
	position.x += speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(-90));
	position.y += speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(-90));
	SetPos(position);
}
