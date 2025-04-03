#include "PlayerAttackManager.h"
#include "PlayerDefaultAttack.h"
#include "PlayerMissileAttack.h"

void PlayerAttackManager::Init()
{
	defaultAttackVec.reserve(AMMUNITION);
	for (int i = 0; i < AMMUNITION; i++)
	{
		PlayerDefaultAttack* defaultAttack = new PlayerDefaultAttack();
		defaultAttack->Init();
		defaultAttackVec.push_back(defaultAttack);
	}
	PlayerMissileAttack* missile = new PlayerMissileAttack();
	missile->Init();
	missileAttackVec.push_back(missile);
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
	PlayerDefaultAttack* attack = nullptr;
	vector<PlayerDefaultAttack*>::iterator iter;
	for (iter = defaultAttackVec.begin(); iter != defaultAttackVec.end(); iter++)
	{
		attack = *iter;

		if(false == attack->IsActive())
		{
			attack->Fire(pos, level);
			break;
		}
	}
}
