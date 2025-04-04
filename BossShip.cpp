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
	// n초동안 파괴 이펙트
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (0 == step && 0.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(60,70,EEffectType::ExplosionNormal);
		DestroyedEffect(60, -50, EEffectType::ExplosionBig);
	}else if (1 == step && 1 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -80, EEffectType::ExplosionSmall);
		DestroyedEffect(-80, 80, EEffectType::ExplosionBig);
	}
	else if (2 == step && 1.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -80, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 110, EEffectType::ExplosionSmall);
	}
	else if (3 == step && 2 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -80, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 110, EEffectType::ExplosionSmall);
	}
	else if (4 == step && 2.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-50, -100, EEffectType::ExplosionNormal);
		DestroyedEffect(-80, 90, EEffectType::ExplosionBig);
	}
	else if (5 == step && 3 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -100, EEffectType::ExplosionNormal);
		DestroyedEffect(-80, 90, EEffectType::ExplosionBig);
	}
	else if (6 == step && 3.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -100, EEffectType::ExplosionNormal);
		DestroyedEffect(-100, 90, EEffectType::ExplosionBig);
	}
	else if (7 == step && 4 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -80, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 110, EEffectType::ExplosionSmall);
	}
	
	if (4 < elapsedTime)
	{
		step = 0;
		elapsedTime = 0;
		state = State::Disappear;
		speed = 200;
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::ShipDestroyed);
	}
}

void BossShip::DestroyedEffect(float dx, float dy, EEffectType type)
{
	FPOINT pos = GetPos();
	
	pos.x += dx;
	pos.y -= dy;

	EffectManager::GetInstance()->PlayEffect(pos, type);

	pos.x -= dx*2;
	pos.y += dy*2;

	EffectManager::GetInstance()->PlayEffect(pos, type);
}

void BossShip::Disappear()
{
	FPOINT destPos = FPOINT{ GetPos().x, WINSIZE_Y + WINSIZE_Y/2};
	float angle = -90.f;

	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();

	FPOINT deltaPos;
	deltaPos.x = deltaTime * speed * cosf(DEG_TO_RAD(angle));
	deltaPos.y = deltaTime * speed * -sinf(DEG_TO_RAD(angle));

	Move(deltaPos);

	if (10 > abs(GetPos().x - destPos.x) && 10 > abs(GetPos().y - destPos.y))
	{
		this->state = State::End;
	}
}
void BossShip::Init()
{
	state = State::Begin;
	elapsedTime = 0;
	this->width = 193 * 1.5;
	this->height = 441 * 1.5;
	speed = 70;

	baseImage = ImageManager::GetInstance()->AddImage(EImageKey::ShipBase,
		L"assets/Sprites/Enemies/Boss/Base.bmp", width, height, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::ShipDestroyed,
		L"assets/Sprites/Enemies/Boss/Base_Destroyed.bmp", width, height, true, RGB(255, 0, 255));
	
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
		this->Destroyed();	// 파괴 이펙트 펑펑?
	}
	else if(State::Disappear == state)
	{
		Disappear();
	}
	else if(State::End == state){

		SetActive(false);
		// dead.
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
		aryCannons[0 + (4 * i)]->SetPos(pos.x - 65 * 1.5 * (1 - i * 2), pos.y - 50 * 1.5);
		aryCannons[1 + (4 * i)]->SetPos(pos.x - 70 * 1.5 * (1 - i * 2), pos.y + 61 * 1.5);
		aryCannons[2 + (4 * i)]->SetPos(pos.x - 42 * 1.5 * (1 - i * 2), pos.y + 88 * 1.5);
		aryCannons[3 + (4 * i)]->SetPos(pos.x - 30 * 1.5 * (1 - i * 2), pos.y + 169 * 1.5);
	}
}
