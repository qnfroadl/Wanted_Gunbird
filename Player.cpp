#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"
#include "ImageManager.h"


void Player::Init()
{
	SetPos(WINSIZE_X / 2, WINSIZE_Y * 0.9);
	speed = 300.0f;
	image = ImageManager::GetInstance()->AddImage("Player",
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		720, 37, 24, 1, true, RGB(255, 0, 255));
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
	//RenderRectAtCenter(hdc, GetPos().x, GetPos().y, 30, 30);	//임시 렌더링
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
	if (currentPos.y <= 0 + 15)
		currentPos.y = 0 + 15;
	else if (currentPos.y >= WINSIZE_Y - 15)
		currentPos.y = WINSIZE_Y - 15;

	SetPos(currentPos);
}

void Player::Fire()
{
	/*
	레벨에 비례해서 공격력, 패턴, 판정크기 증가
	(증가시킬 항목은 회의 후 선택)
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
