#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"
#include "ImageManager.h"


void Player::Init()
{
	AddTag(GameTag::Player);
	SetPos(WINSIZE_X / 2, WINSIZE_Y * 0.9);
	speed = 300.0f;
	image = ImageManager::GetInstance()->AddImage("Player",
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744, 41, 24, 1, true, RGB(255, 0, 255));
	if (!image)
		return;

	animFrame = 0;
	elapsedFrame = 0;

	attackLevel = 1;
}

void Player::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}

void Player::Update()
{
	elapsedFrame++;
	if (elapsedFrame > 1)
	{
		elapsedFrame = 0;
		animFrame++;
		if (animFrame > image->GetMaxFrameX())
		{
			animFrame = 0;
		}
	}
	// 시간이 나면 좌,우 움직임 스프라이트도 넣는다
	float moveAngle = -999.0f;
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
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
	{
		moveAngle = 0.0f;
		movementActive = true;
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 225.0f;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 315.0f;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 135.0f;
		movementActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 45.0f;
		movementActive = true;
	}
	if(movementActive)
		Move(moveAngle);
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		Fire();
}

void Player::Render(HDC hdc)
{
	//스프라이트가 흔들리는걸 고쳐야함. 스프라이트 크기를 균일하게 다시 쪼갤것
	if (image)
	{
		image->FrameRender(hdc, GetPos().x, GetPos().y, animFrame, 0, false);
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
}

void Player::Fire()
{
	/*
	레벨에 비례해서 총알 추가
	4레벨에는 미사일 추가
	미사일 매니저가 있어야 하겟는데
	*/
	switch (attackLevel)
	{
	case 2:
		//2레벨 공격
		break;
	case 3:
		//3레벨 공격
		break;
	case 4:
		//4레벨 공격
		break;
	default:
		//기본(1레벨) 공격
		
		break;
	}
}

void Player::IncreaseAttackLevel()
{
	if (true/*레벨 업 조건*/)
	{
		if (attackLevel >= 4)
			attackLevel = 4;
		else
			attackLevel++;
	}
}

void Player::ActivateBomb()
{
	if (bombCount <= 0)
		return;
	/* 
	 폭탄은 missileMgr에서 구현?
	 폭탄의 collision과 겹치는 collision 계산
	 겹치면 release()
	*/
}
