#include "BossBird.h"

#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "CollisionManager.h"
#include "TimerManager.h"
#include "EffectManager.h"

#define RATIO 1.5f
void BossBird::Appear()
{
	// È­¸é »ó´Ü±îÁö ÀÌµ¿ÇÏ°í µµÂøÇÏ¸é ³¯°³ÇË.
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (1 < elapsedTime && elapsedTime < 2)
	{
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdAppear2);
	}
	else if (2 <= elapsedTime)
	{
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdBase);
	}

}

void BossBird::MoveMove()
{
	//ÁÂ¿ì ¹«ºù °è¼Ó.

	
}

void BossBird::Destroyed()
{

}

void BossBird::DestroyedEffect(float dx, float dy, EEffectType type)
{

}

void BossBird::Disappear()
{

}

void BossBird::Damaged(int& hp, int damage)
{
	hp -= damage;
	if (hp < 0)
	{
		hp = 0;
	}

	if (leftHP == 0)
	{

	}
	else if (rightHP == 0)
	{

	}
	else if (bodyHP == 0)
	{

	}


	// Ã¼·Â ±ï±â
	if (bodyHP + leftHP + rightHP == 0)
	{	// »ç¸Á
		state = State::Destroyed;
	}
}

void BossBird::On_CollisionDetected(GameObject* obj, int& hp)
{
	if (obj->FindTag(GameTag::PlayerDefaultAttack))
	{
		obj->SetActive(false);
		Damaged(hp, 1);
		EffectManager::GetInstance()->PlayEffect(GetPos(), EEffectType::ShotImpact);
	}
	else if (obj->FindTag(GameTag::PlayerMissileAttack))
	{
		obj->SetActive(false);
		Damaged(hp, 2);
		EffectManager::GetInstance()->PlayEffect(GetPos(), EEffectType::ShotImpact);
	}
	
}


void BossBird::Init()
{
	left = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Enemy, this, RECT{});
	left->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj, leftHP);
		});
	body = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Enemy, this, RECT{});
	body->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj, bodyHP);
		});
	right = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Enemy, this, RECT{});
	right->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj, rightHP);
		});

	leftHP = 50;
	rightHP = 50;
	bodyHP = 100;

	baseImage = ImageManager::GetInstance()->AddImage(EImageKey::BirdAppear1, L"assets/Sprites/Enemies/Boss/Bird_Appear1.bmp", 75 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdAppear2, L"assets/Sprites/Enemies/Boss/Bird_Appear2.bmp", 179 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdBase, L"assets/Sprites/Enemies/Boss/Bird_Appear3.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroyLeft, L"assets/Sprites/Enemies/Boss/Bird_Destroy_left.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroyRight, L"assets/Sprites/Enemies/Boss/Bird_Destroy_Right.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroy, L"assets/Sprites/Enemies/Boss/Bird_Destroy.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));

	propellerImage = ImageManager::GetInstance()->AddImage(EImageKey::BirdPropeller, 
		L"assets/Sprites/Enemies/Boss/propeller.bmp", 240 * RATIO, 35 * RATIO, 3, 1, true, RGB(255,0,255));

}

void BossBird::Update()
{
	if (State::Begin == state)
	{
		Appear();
	}
	else if (State::Fight == state)
	{
		MoveMove();
		
	}
	else if (State::Destroyed == state)
	{
		this->Destroyed();	// ÆÄ±« ÀÌÆåÆ® ÆãÆã?
	}
	else if (State::Disappear == state)
	{
		Disappear();
	}
	else if (State::End == state) {

		SetActive(false);
		// dead.
	}



	// ÇÁ·ÎÆç·¯
	propellerTime += TimerManager::GetInstance()->GetDeltaTime();
	if (0.1 <= propellerTime)
	{
		propellerTime = 0;
		curFrame++;
		if (propellerImage->GetMaxFrameX() <= curFrame)
		{
			curFrame = 0;
		}
	}
}

void BossBird::Render(HDC hdc)
{
	baseImage->RenderCenter(hdc, GetPos().x, GetPos().y);
	propellerImage->FrameRender(hdc, GetPos().x, GetPos().y -10, curFrame, 0);
}

void BossBird::Release()
{
	CollisionManager::GetInstance()->DeleteCollision(left);
	CollisionManager::GetInstance()->DeleteCollision(body);
	CollisionManager::GetInstance()->DeleteCollision(right);

		
}

void BossBird::SetTarget(GameActor* target)
{
	this->target = target;
}
