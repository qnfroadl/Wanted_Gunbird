#include "PlayerAttackManager.h"
#include "PlayerDefaultAttack.h"
#include "PlayerMissileAttack.h"
#include <math.h>

void PlayerAttackManager::Fire(const FPOINT& pos, int level, vector<PlayerDefaultAttack*>& attack)
{
	FPOINT leftPos = pos;
	FPOINT rightPos = pos;
	int gap_X = 9;
	int gap_Y = 15;
	for (int i = 0; i < level; i++)
	{
		leftPos.x -= gap_X;
		leftPos.y += gap_Y;
		rightPos.x += gap_X;
		rightPos.y += gap_Y;

		attack[(i * 2)]->Fire(leftPos);
		attack[(i * 2) + 1]->Fire(rightPos);

	}

	if (level == 3)
	{
		leftPos.x -= gap_X;
		leftPos.y += gap_Y;
		rightPos.x += gap_X;
		rightPos.y += gap_Y;

		attack[6]->Fire(leftPos);
		attack[7]->Fire(rightPos);

	}

}
void PlayerAttackManager::Init()
{
	defaultAttackVec.reserve(AMMUNITION);
	for (int i = 0; i < AMMUNITION; i++)
	{
		PlayerDefaultAttack* defaultAttack = new PlayerDefaultAttack();
		defaultAttack->Init();
		defaultAttackVec.push_back(defaultAttack);
		PlayerMissileAttack* missile = new PlayerMissileAttack();
		missile->Init();
		missileAttackVec.push_back(missile);
	}
}

void PlayerAttackManager::Release()
{
	for (auto const& iter : defaultAttackVec)
	{
		iter->Release();
		delete iter;
	}
	defaultAttackVec.clear();

	for (auto const& iter : missileAttackVec)
	{
		iter->Release();
		delete iter;
	}
	missileAttackVec.clear();
}

void PlayerAttackManager::Update()
{
	for (auto const& defaultAttack : defaultAttackVec)
	{
		defaultAttack->Update();
	}
	for (auto const& missileAttack : missileAttackVec)
	{
		missileAttack->Update();
	}
}

void PlayerAttackManager::Render(HDC hdc)
{
	for (auto const& defaultAttack : defaultAttackVec)
	{
		defaultAttack->Render(hdc);
	}
	for (auto const& missileAttack : missileAttackVec)
	{
		missileAttack->Render(hdc);
	}
}

void PlayerAttackManager::Fire(FPOINT pos, int level)
{
	// 1레벨은 2발, 2레벨4발, 3레벨8발.

	vector<PlayerDefaultAttack*> vecAttack;

	PlayerDefaultAttack* attack = nullptr;
	vector<PlayerDefaultAttack*>::iterator iter;

	int attackCount = (1 << level);
	if (level < 4)
	{
		for (iter = defaultAttackVec.begin(); iter != defaultAttackVec.end(); iter++)
		{
			attack = *iter;

			if (false == attack->IsActive())
			{
				vecAttack.push_back(attack);
				if (attackCount == vecAttack.size())
				{
					break;
				}
			}
		}

		if (attackCount == vecAttack.size())
		{
			Fire(pos, level, vecAttack);
		}
		
	}
}