#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"


void Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y * 0.9 };
	speed = 100.0f;
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
	float moveAngle = -999.0f;

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
	{
		moveAngle = 270.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
	{
		moveAngle = 90.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
	{
		moveAngle = 180.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
	{
		moveAngle = 0.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 225.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 315.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 135.0f;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 45.0f;
	}
		Move(moveAngle);
	
}

void Player::Render(HDC hdc)
{
	RenderRectAtCenter(hdc, pos.x, pos.y, 30, 30);	//ÀÓ½Ã ·»´õ¸µ
}

void Player::Move(float degree)
{
	pos.x = speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(degree));
	pos.y = speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(degree));
}

void Player::Fire()
{
}