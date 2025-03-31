#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"


void Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y * 0.9 };
	speed = 300.0f;
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
	bool isActive = false;

	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP))
	{
		moveAngle = 270.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN))
	{
		moveAngle = 90.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT))
	{
		moveAngle = 180.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT))
	{
		moveAngle = 0.0f;
		isActive = true;
	}
	if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 225.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_UP) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 315.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_LEFT)))
	{
		moveAngle = 135.0f;
		isActive = true;
	}
	else if (KeyManager::GetInstance()->IsStayKeyDown(VK_DOWN) &&
		(KeyManager::GetInstance()->IsStayKeyDown(VK_RIGHT)))
	{
		moveAngle = 45.0f;
		isActive = true;
	}
	if(isActive)
		Move(moveAngle);
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE))
		Fire();
}

void Player::Render(HDC hdc)
{
	RenderRectAtCenter(hdc, pos.x, pos.y, 30, 30);	//ÀÓ½Ã ·»´õ¸µ
}

void Player::Move(float degree)
{
	pos.x += speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(degree));
	if (pos.x <= 0)
		pos.x = 0;
	else if (pos.x >= WINSIZE_X - 15)
		pos.x = WINSIZE_X - 15;

	pos.y += speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(degree));
	if (pos.y <= 0 + 15)
		pos.y = 0 + 15;
	else if (pos.y >= WINSIZE_Y - 15)
		pos.y = WINSIZE_Y - 15;
}

void Player::Fire()
{
}