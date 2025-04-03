#include "Player.h"
#include "GameActor.h"
#include "CommonFunction.h"
#include "TimerManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "PlayerDefaultAttack.h"
#include "CollisionManager.h"

void Player::CollisionDetected(GameObject* obj)
{
	auto tags = obj->GetTags();
	if (0 < tags.count(GameTag::Player))
	{
		if (0 < tags.count(GameTag::Enemy))
		{
			// ������ �� �Ѿ˰� �ε�����.
			this->SetActive(false);	//Enemy��Ȱ��
			obj->SetActive(false);	//Bullet��Ȱ��
		}
		else
		{
			//���ϰ� �ε�����.
			this->SetActive(false);	// Enemy��Ȱ��
			obj->SetActive(false);	// Rocket ��Ȱ��
		}
	}
}

void Player::Init()
{
	animFrame = 0;
	elapsedFrame = 0;
	attackLevel = 1;

	AddTag(GameTag::Player);
	SetPos(WINSIZE_X / 2, WINSIZE_Y * 0.9);
	speed = 300.0f;
	image = ImageManager::GetInstance()->AddImage(EImageKey::Player,
		TEXT("assets/Sprites/Characters/testu_idle_spriteMerge.bmp"),
		744, 41, 24, 1, true, RGB(255, 0, 255));
	if (!image)
		return;

	missile = new PlayerDefaultAttack;
	missile->Init();
}

void Player::Release()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}

	if (missile)
	{
		missile->Release();
		delete missile;
		missile = nullptr;
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
	// �ð��� ���� ��,�� ������ ��������Ʈ�� �ִ´�
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

	missile->Update();
}

void Player::Render(HDC hdc)
{
	if (image)
	{
		image->FrameRender(hdc, GetPos().x, GetPos().y, animFrame, 0, false);
	}
	if (missile)
	{
		missile->Render(hdc);
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
	������ ����ؼ� �Ѿ� �߰�
	4�������� �̻��� �߰�
	�̻��� �Ŵ����� �־�� �ϰٴµ�
	*/
	missile->Fire(GetPos(), attackLevel);
}

void Player::IncreaseAttackLevel()
{
	if (true/*���� �� ����*/)
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
	 ��ź�� missileMgr���� ����?
	 ��ź�� collision�� ��ġ�� collision ���
	 ��ġ�� release()
	*/
}
