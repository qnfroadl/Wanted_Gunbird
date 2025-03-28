#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"

void Player::Move(float degree)
{
	pos.x = speed * TimerManager::GetInstance()->GetDeltaTime() * cosf(DEG_TO_RAD(degree));
	pos.y = speed * TimerManager::GetInstance()->GetDeltaTime() * sinf(DEG_TO_RAD(degree));
}

void Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y * 0.1 };
}

void Player::Release()
{
}

void Player::Update()
{
}

void Player::Render(HDC hdc)
{
}
