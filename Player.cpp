#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "PlayerAttackManager.h"
#include "PlayerDefaultAttack.h"
#include "PlayerMissileAttack.h"
#include "PlayerBomb.h"
#include "CollisionManager.h"
#include "Item.h"

#define PLAYERWITHD (744/24*2)
#define PLAYERHEIGHT 41*2

void Player::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(GameTag::PowerUp))
	{
		IncreaseAttackLevel();
	}
	else if (0 < tags.count(GameTag::BombUp))
	{
		IncreaseBomb();
	}
	if (0 < tags.count(GameTag::Enemy))
	{
		Dead();
		if (life > 0)
		{
			Respawn();
			/*respawnTime += TimerManager::GetInstance()->GetDeltaTime();
			if (respawnTime >= 1.0f)
			{
				Respawn();
				respawnTime = 0.0f;
			}*/
		}
	}
}

void Player::Init()
{
	life = 2;
	animFrame = 0;
	elapsedFrame = 0;
	attackLevel = 1;
	bombCount = 2;
	bRightMove = false;
	bLeftMove = false;
	respawnTime = 0.0f;
	bIsDead = false;
	AddTag(GameTag::Player);
	SetPos(WINSIZE_X / 2, WINSIZE_Y * 0.9);
	speed = 500.0f;
	image = ImageManager::GetInstance()->AddImage(EImageKey::Player,
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744*2, 41*2, 24, 1, true, RGB(255, 0, 255));
	if (!image)
		return;
	/*rightMoveImage = ImageManager::GetInstance()->AddImage(EImageKey::Player,
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744 * 2, 41 * 2, 24, 1, true, RGB(255, 0, 255));
	if (!rightMoveImage)
		return;
	leftMoveImage = ImageManager::GetInstance()->AddImage(EImageKey::Player,
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744 * 2, 41 * 2, 24, 1, true, RGB(255, 0, 255));
	if (!leftMoveImage)
		return;*/

	attackManager = new PlayerAttackManager;
	attackManager->Init();
	playerBomb = new PlayerBomb;
	playerBomb->Init(GetPos());
	FPOINT pos = GetPos();
	RECT defaultRect = { pos.x - (PLAYERWITHD/2), pos.y - (PLAYERHEIGHT/2), pos.x + (PLAYERWITHD/2), pos.y + (PLAYERHEIGHT/2) };
	playerCollision = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Player, this, defaultRect);
	playerCollision->Bind([&](GameObject* obj)
		{
			this->CollisionDetected(obj);
		}
	);
}

void Player::Release()
{
	/*if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}

	if (leftMoveImage)
	{
		leftMoveImage->Release();
		delete leftMoveImage;
		leftMoveImage = nullptr;
	}

	if (rightMoveImage)
	{
		rightMoveImage->Release();
		delete rightMoveImage;
		rightMoveImage = nullptr;
	}*/

	if (attackManager)
	{
		attackManager->Release();
		delete attackManager;
		attackManager = nullptr;
	}
	
	if (playerBomb)
	{
		playerBomb->Release();
		delete playerBomb;
		playerBomb = nullptr;
	}
}

void Player::Update()
{
	elapsedFrame++;
	if (elapsedFrame > 1)
	{
		elapsedFrame = 0;
		animFrame++;
		if (animFrame >= image->GetMaxFrameX())
		{
			animFrame = 0;
		}
	}
	// 시간이 나면 좌,우 움직임 스프라이트도 넣는다
	float moveAngle = 0;
	bool movementActive = false;

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
	{
		moveAngle = 270.0f;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
	{
		moveAngle = 90.0f;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
	{
		moveAngle = 180.0f;
		bLeftMove = true;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
	{
		moveAngle = 0.0f;
		bRightMove = true;
		movementActive = true;
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 225.0f;
		bLeftMove = true;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 315.0f;
		bRightMove = true;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 135.0f;
		bLeftMove = true;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 45.0f;
		bRightMove = true;
		movementActive = true;
	}
	else
	{
		bLeftMove = false;
		bRightMove = false;
	}
	if(movementActive)
		Move(moveAngle);

	if (KeyManager::GetInstance()->IsOnceKeyDown('A'))
		Fire();
	if (KeyManager::GetInstance()->IsOnceKeyDown('S'))
	{
		ActivateBomb();
		playerBomb->Update();
	
	}
	if (attackManager)
	{
		attackManager->Update();
	}
}

void Player::Render(HDC hdc)
{
	if (playerBomb)
	{
		playerBomb->Render(hdc, GetPos());
	}/*
	if (bLeftMove && leftMoveImage)
	{
		leftMoveImage->FrameRender(hdc, GetPos().x, GetPos().y, animFrame, 0, false);
	}
	if (bRightMove && rightMoveImage)
	{
		rightMoveImage->FrameRender(hdc, GetPos().x, GetPos().y, animFrame, 0, false);
	}*/
	if (image && !bIsDead)
	{
		image->FrameRender(hdc, GetPos().x, GetPos().y, animFrame, 0, false);
	}
	if (attackManager)
	{
		attackManager->Render(hdc);
	}
}

void Player::Move(float degree)
{
	FPOINT currentPos = GetPos();

	currentPos.x += speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(degree));
	if (currentPos.x <= 0 + 15)
		currentPos.x = 0 + 15;
	else if (currentPos.x >= WINSIZE_X - 15)
		currentPos.x = WINSIZE_X - 15;

	currentPos.y += speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(degree));
	if (currentPos.y <= 0 + 24)
		currentPos.y = 0 + 24;
	else if (currentPos.y >= WINSIZE_Y - 24)
		currentPos.y = WINSIZE_Y - 24;

	SetPos(currentPos);
	playerCollision->SetRect(GetRectAtCenter(currentPos.x, currentPos.y, PLAYERWITHD, PLAYERHEIGHT));
}

void Player::Fire()
{
	/*
	레벨에 비례해서 총알 추가
	4레벨에는 미사일 추가
	미사일 매니저가 있어야 하겟는데
	*/
	if(attackManager)
	{
		attackManager->Fire(GetPos(), attackLevel);
	}
}

void Player::IncreaseAttackLevel()
{
	if (attackLevel >= 4)
		attackLevel = 4;
	else
		attackLevel++;
}

void Player::IncreaseBomb()
{
	bombCount++;
}

void Player::ActivateBomb()
{
	if (bombCount <= 0)
		return;
	playerBomb->BombActivate(GetPos());
	bombCount--;
	/* 
	 폭탄은 missileMgr에서 구현?
	 폭탄의 collision과 겹치는 collision 계산
	 겹치면 release()
	*/
}

int Player::GetBombCount()
{
	return this->bombCount;
}

void Player::Dead()
{
	//SetActive(false);
	bIsDead = true;
	playerCollision->SetActive(false);
	attackManager->SetActive(false);
	playerBomb->SetActive(false);
}

void Player::Respawn()
{
	life--;
	bIsDead = false;
	SetPos(WINSIZE_X / 2, WINSIZE_Y * 0.9);
	playerCollision->SetActive(true);
	attackManager->SetActive(true);
	playerBomb->SetActive(true);
	ImageManager::GetInstance()->AddImage(EImageKey::Player,
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744 * 2, 41 * 2, 24, 1, true, RGB(255, 0, 255));
}