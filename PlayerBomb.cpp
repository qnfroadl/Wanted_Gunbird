#include "PlayerBomb.h"
#include "Image.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "CollisionManager.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "Enemy.h"
#include "EffectManager.h"

#define bombWidth (1008/36)
#define bombHeight (57)

void PlayerBomb::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(GameTag::Enemy))
	{
		Enemy* enemy = static_cast<Enemy*>(obj);
		enemy->Damaged(1000);

		this->SetActive(false);	// Enemy비활성
		this->bombCollision->SetActive(false);
	}
}

void PlayerBomb::Init(FPOINT playerPos)
{
	//수정필요
	animFrame = 0;
	elapsedFrame = 0;
	bombImage = ImageManager::GetInstance()->AddImage(EImageKey::PlayerBomb,
		L"assets/Sprites/Characters/testu_Bomb.bmp",
		1008, 57, 36, 1, true, RGB(255, 0, 255));
	if (!bombImage)
		return;

	pos = playerPos;
	RECT bombtRect = { pos.x - bombWidth / 2, pos.y - bombHeight / 2, pos.x + bombWidth / 2, pos.y + bombHeight / 2 };

	bombCollision = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::PlayerAttack, this, bombtRect);
	bombCollision->Bind([&](GameObject* obj)
		{
			this->CollisionDetected(obj);
		});
	SetActive(false);
}

void PlayerBomb::Release()
{
	if (!bombImage)
	{
		bombImage->Release();
		delete bombImage;
		bombImage = nullptr;
	}
}

void PlayerBomb::Update(FPOINT playerPos)
{
	if(IsActive())
	{
		elapsedFrame += TimerManager::GetInstance()->GetDeltaTime();
		if (elapsedFrame > 1)
		{
			animFrame++;
			if (animFrame >= bombImage->GetMaxFrameX())
			{
				animFrame = 0;
			}
			elapsedFrame = 0;
		}
	}
	
}

void PlayerBomb::Render(HDC hdc)
{
	if (IsActive())
	{
		if (bombImage)
		{
			bombImage->Render(hdc, pos.x, pos.y);
		}
	}

}

void PlayerBomb::BombActivate(FPOINT pos)
{
	SetPos(pos);
	SetActive(true);
	bombCollision->SetActive(true);
}
