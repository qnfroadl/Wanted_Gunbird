#include "BossShip.h"

#include "ImageManager.h"
#include "Image.h"
#include "ShipCanon.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "EffectManager.h"

void BossShip::Appear()
{
	// 어디서 스폰될지 모르겠지만, 해당 위치까지 일단 간다.
	// WINSIZE_X / 2, WINSIZE_Y/4
	FPOINT destPos = FPOINT{ WINSIZE_X / 2, WINSIZE_Y / 4 };

	float angle = GetAngle(GetPos(), destPos);
	
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	
	FPOINT deltaPos;
	deltaPos.x = deltaTime * speed * cosf(angle);
	deltaPos.y = deltaTime * speed * -sinf(angle);

	Move(deltaPos);

	if (10 > abs(GetPos().x - destPos.x) && 10 > abs(GetPos().y - destPos.y))
	{
		this->state = State::Fight;
		moveAngle = 180;
	}
}
void BossShip::MoveMove()
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	FPOINT deltaPos;
	deltaPos.x = deltaTime * speed * cosf(DEG_TO_RAD(moveAngle));
	deltaPos.y = deltaTime * speed * -sinf(DEG_TO_RAD(moveAngle));

	Move(deltaPos);

	FPOINT leftPos = GetPos();
	FPOINT rightPos = GetPos();

	leftPos.x -= this->width/2;
	rightPos.x += this->width/2;


	if (IsOutofScreen(leftPos))
	{
		moveAngle = 0;
	}
	else if (IsOutofScreen(rightPos))
	{
		moveAngle = 180;
	}

}

void BossShip::Destroyed()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();

	EffectManager::GetInstance();
	
}

void BossShip::Disappear()
{
	
}
void BossShip::Init()
{
	state = State::Begin;
	elapsedTime = 0;
	this->width = 193;
	this->height = 441;
	speed = 50;

	baseImage = ImageManager::GetInstance()->AddImage(EImageKey::ShipBase,
		L"assets/Sprites/Enemies/Boss/Base.bmp", width, height, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyedLeft,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed_Left.bmp", 65, 120, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyedRight,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed_Right.bmp", 64, 120, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyed,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed.bmp", width, height, true, RGB(255, 0, 255));
	
	baseDestroyLeft = nullptr;
	baseDestroyRight = nullptr;

	for (int i = 0; i < 8; i++)
	{
		aryCannons[i] = new ShipCannon();
		aryCannons[i]->Init();
	}

	bCannonsLive = true;
}

void BossShip::Update()
{
	bool bCannonsAllDie = true;

	for (int i = 0; i < 8; i++)
	{
		if (aryCannons[i]->IsActive())
		{
			bCannonsAllDie = false;
			aryCannons[i]->Update();
		}
	}

	if (State::Begin == state)
	{
		Appear();
	}
	else if (State::Fight == state)
	{
		MoveMove();
		if (bCannonsAllDie)
		{
			state = State::Destroyed;
		}
	}
	else if(State::Destroyed == state)
	{
		Destroyed();	// 파괴 이펙트 펑펑?
	}
	else {
		Disappear();
	}
	
}

void BossShip::Render(HDC hdc)
{
	baseImage->RenderCenter(hdc, GetPos().x, GetPos().y);

	for (int i = 0; i < 8; i++)
	{
		if (aryCannons[i]->IsActive())
		{
			aryCannons[i]->Render(hdc);
		}
	}
}

void BossShip::Release()
{
	for (int i = 0; i < 8; i++)
	{
		aryCannons[i]->Release();	
	}
}

void BossShip::SetTarget(GameActor* target)
{
	for (int i = 0; i < 8; i++)
	{
		aryCannons[i]->SetTarget(target);
	}
}

void BossShip::Move(const FPOINT& movePos)
{
	this->AddPos(movePos);
	CannonPosUpdate();
}

void BossShip::CannonPosUpdate()
{
	FPOINT pos = GetPos();
	for (int i = 0; i < 2; i++)
	{
		aryCannons[0 + (4 * i)]->SetPos(pos.x - 70 * (1 - i * 2), pos.y - 50);
		aryCannons[1 + (4 * i)]->SetPos(pos.x - 76 * (1 - i * 2), pos.y + 61);
		aryCannons[2 + (4 * i)]->SetPos(pos.x - 45 * (1 - i * 2), pos.y + 88);
		aryCannons[3 + (4 * i)]->SetPos(pos.x - 35 * (1 - i * 2), pos.y + 169);
	}
}
