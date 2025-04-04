#include "BossBird.h"

#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "CollisionManager.h"
#include "TimerManager.h"
#include "EffectManager.h"
#include "ShotManager.h"

#define RATIO 1.5f
void BossBird::Appear()
{
	if (Move(FPOINT{ WINSIZE_X / 2, WINSIZE_Y / 4 }))
	{
		// È­¸é »ó´Ü±îÁö ÀÌµ¿ÇÏ°í µµÂøÇÏ¸é ³¯°³ÇË.
		elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
		if (0.5 < elapsedTime && elapsedTime < 1)
		{
			baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdAppear2);
		}
		else if (1 <= elapsedTime)
		{
			baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdBase);
			left->SetActive(true);
			right->SetActive(true);
			this->state = State::Fight;
			speed = 100;
			elapsedTime = 0;
		}
	}
}

void BossBird::Fight()	//Fight
{
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	elapsedTime += deltaTime;

	FPOINT deltaPos;
	deltaPos.x = deltaTime * speed * cosf(DEG_TO_RAD(moveAngle));
	deltaPos.y = deltaTime * speed * -sinf(DEG_TO_RAD(moveAngle));

	AddPos(deltaPos);

	FPOINT leftPos = GetPos();
	FPOINT rightPos = GetPos();

	leftPos.x -= this->width / 2;
	rightPos.x += this->width / 2;


	if (IsOutofScreen(leftPos))
	{
		moveAngle = 0;
	}
	else if (IsOutofScreen(rightPos))
	{
		moveAngle = 180;
	}

	if (1.5 < elapsedTime)
	{
		elapsedTime = 0.f;
		Attack();
	}

}

void BossBird::Destroyed()
{
	// nÃÊµ¿¾È ÆÄ±« ÀÌÆåÆ®
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (0 == step && 0.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(60, 70, EEffectType::ExplosionNormal);
		DestroyedEffect(60, -50, EEffectType::ExplosionBig);
	}
	else if (1 == step && 1 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -80, EEffectType::ExplosionSmall);
		DestroyedEffect(-80, 80, EEffectType::ExplosionBig);
	}
	else if (2 == step && 1.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -40, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 55, EEffectType::ExplosionSmall);
	}
	else if (3 == step && 2 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -40, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 55, EEffectType::ExplosionSmall);
	}
	else if (4 == step && 2.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-50, -50, EEffectType::ExplosionNormal);
		DestroyedEffect(-80, 45, EEffectType::ExplosionBig);
	}
	else if (5 == step && 3 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -50, EEffectType::ExplosionNormal);
		DestroyedEffect(-80, 40, EEffectType::ExplosionBig);
	}
	else if (6 == step && 3.5 < elapsedTime)
	{
		step++;
		DestroyedEffect(-80, -50, EEffectType::ExplosionNormal);
		DestroyedEffect(-100, 40, EEffectType::ExplosionBig);
	}
	else if (7 == step && 4 < elapsedTime)
	{
		step++;
		DestroyedEffect(-100, -40, EEffectType::ExplosionBig);
		DestroyedEffect(-80, 50, EEffectType::ExplosionSmall);
	}

	if (4 < elapsedTime)
	{
		step = 0;
		elapsedTime = 0;
		state = State::Disappear;
		speed = 300;
	}
}

void BossBird::DestroyedEffect(float dx, float dy, EEffectType type)
{
	FPOINT pos = GetPos();

	pos.x += dx;
	pos.y -= (dy + 80);

	EffectManager::GetInstance()->PlayEffect(pos, type);

	pos.x -= dx * 2;
	pos.y += (dy * 2) - 80;

	EffectManager::GetInstance()->PlayEffect(pos, type);
}

void BossBird::Disappear()
{

}

bool BossBird::Move(const FPOINT& destPos)
{
	float angle = GetAngle(GetPos(), destPos);
	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();

	FPOINT pos = GetPos();
	if (abs(pos.x - destPos.x) < 10 && abs(pos.y - destPos.y) < 10)
	{
		// ÀÌ¹Ì µµÂøÇß´Ù.
		return true;
	}

	pos.x += deltaTime * speed * cosf(angle);
	pos.y += deltaTime * speed * -sinf(angle);
	SetPos(pos);

	return false;
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
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdDestroyLeft);
		left->SetActive(false);
	}
	if (rightHP == 0)
	{
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdDestroyRight);
		right->SetActive(false);
	}
	if (leftHP == 0 && rightHP == 0)
	{
		baseImage = ImageManager::GetInstance()->FindImage(EImageKey::BirdDestroy);
		left->SetActive(false);
		right->SetActive(false);
	}

	// Ã¼·Â ±ï±â
	if (leftHP + rightHP == 0)
	{	// »ç¸Á
		state = State::Destroyed;
		elapsedTime = 0;
	}
}

void BossBird::On_CollisionDetected(GameObject* obj, int& hp)
{
	if (obj->FindTag(GameTag::PlayerDefaultAttack))
	{
		obj->SetActive(false);
		Damaged(hp, 1);
		// EffectManager::GetInstance()->PlayEffect(GetPos(), EEffectType::ShotImpact);
	}
	else if (obj->FindTag(GameTag::PlayerMissileAttack))
	{
		obj->SetActive(false);
		Damaged(hp, 2);
		// EffectManager::GetInstance()->PlayEffect(GetPos(), EEffectType::ShotImpact);
	}
	
}

void BossBird::UpdateCollisionRect()
{
	FPOINT pos = GetPos();

	left->SetRect(GetRectAtCenter(pos.x - 60 * RATIO, pos.y-80, 120 * RATIO, 30 * RATIO));
	right->SetRect(GetRectAtCenter(pos.x + 60 * RATIO, pos.y-80, 120 * RATIO, 30 * RATIO));

}

void BossBird::Attack()
{
	FPOINT pos = GetPos();

	if (leftHP == 0)
	{	//¿ìÃø¸¸ °­ÇÑ °ø°Ý
		// ShotManager::GetInstance()->Fire()
	}
	else if (rightHP == 0)
	{	//ÁÂÃø¸¸ °­ÇÑ °ø°Ý.

	}
	else 
	{	// ³ÐÀº °ø°Ý.
		attackStep++;
		if (attackStep < 5)
		{
			
			for (int i = 0; i < 5; i++)
			{
				ShotManager::GetInstance()->Fire(pos.x + leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 + 10, 300);
				ShotManager::GetInstance()->Fire(pos.x + leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 - 10, 300);
				ShotManager::GetInstance()->Fire(pos.x - leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 + 10, 300);
				ShotManager::GetInstance()->Fire(pos.x - leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 - 10, 300);
			}
		}
		else if(attackStep < 10)
		{
			for (int i = 0; i < 5; i++)
			{
				ShotManager::GetInstance()->Fire(pos.x + leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 + 10, 300);
				ShotManager::GetInstance()->Fire(pos.x + leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 - 10, 300);
				ShotManager::GetInstance()->Fire(pos.x - leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 + 10, 300);
				ShotManager::GetInstance()->Fire(pos.x - leftAttackPos[i].x, pos.y + leftAttackPos[i].y, -90 - 10, 300);
			}
		}
	}
}

void BossBird::Init()
{
	AddTag(GameTag::BossEnemy);
	left = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Enemy, this, RECT{});
	left->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj, leftHP);
		});
	
	right = CollisionManager::GetInstance()->CreateCollisionRect(CollisionLayer::Enemy, this, RECT{});
	right->Bind([&](GameObject* obj)
		{
			On_CollisionDetected(obj, rightHP);
		});

	left->SetActive(false);
	right->SetActive(false);

	this->width = 253 * RATIO;
	this->height = 100 * RATIO;
	leftHP = 50;
	rightHP = 50;
	speed = 300;
	attackStep = 0;

	baseImage = ImageManager::GetInstance()->AddImage(EImageKey::BirdAppear1, L"assets/Sprites/Enemies/Boss/Bird_Appear1.bmp", 75 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdAppear2, L"assets/Sprites/Enemies/Boss/Bird_Appear2.bmp", 179 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdBase, L"assets/Sprites/Enemies/Boss/Bird_Appear3.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255,0,255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroyLeft, L"assets/Sprites/Enemies/Boss/Bird_Destroy_left.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroyRight, L"assets/Sprites/Enemies/Boss/Bird_Destroy_Right.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));
	ImageManager::GetInstance()->AddImage(EImageKey::BirdDestroy, L"assets/Sprites/Enemies/Boss/Bird_Destroy.bmp", 253 * RATIO, 295 * RATIO, true, RGB(255, 0, 255));

	propellerImage = ImageManager::GetInstance()->AddImage(EImageKey::BirdPropeller, 
		L"assets/Sprites/Enemies/Boss/propeller.bmp", 240 * RATIO, 35 * RATIO, 3, 1, true, RGB(255,0,255));

	leftAttackPos[0] = FPOINT{ -93* RATIO, -56* RATIO};
	leftAttackPos[1] = FPOINT{ -85* RATIO, -47* RATIO};
	leftAttackPos[2] = FPOINT{ -69* RATIO, -42* RATIO};
	leftAttackPos[3] = FPOINT{ -51* RATIO, -40* RATIO};
	leftAttackPos[4] = FPOINT{ -36* RATIO, -39* RATIO};

}

void BossBird::Update()
{
	UpdateCollisionRect();

	if (State::Begin == state)
	{
		Appear();
	}
	else if (State::Fight == state)
	{
		Fight();
		
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
	CollisionManager::GetInstance()->DeleteCollision(right);
		
}

void BossBird::SetTarget(GameActor* target)
{
	this->target = target;
}
