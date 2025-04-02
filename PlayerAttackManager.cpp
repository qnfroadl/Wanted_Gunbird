#include "PlayerAttackManager.h"
#include "PlayerDefaultAttack.h"

void PlayerAttackManager::Init()
{
	defaultAttackVec.reserve(AMMUNITION);
}

void PlayerAttackManager::Release()
{
	for (auto const& iter : defaultAttackVec)
	{
		iter->Release();
		delete iter;
	}
}

void PlayerAttackManager::Update()
{
	PlayerDefaultAttack* attack = nullptr;
	vector<PlayerDefaultAttack*>::iterator iter;
	for (iter = defaultAttackVec.begin(); iter != defaultAttackVec.end(); iter++)
	{
		attack = *iter;
		attack->Update();
	}
}

void PlayerAttackManager::Render(HDC hdc)
{
	PlayerDefaultAttack* attack = nullptr;
	vector<PlayerDefaultAttack*>::iterator iter;
	for (iter = defaultAttackVec.begin(); iter != defaultAttackVec.end(); iter++)
	{
		attack = *iter;
		attack->Render(hdc);
	}
}

void PlayerAttackManager::Fire(FPOINT pos, int level)
{
	PlayerDefaultAttack* attack = nullptr;
	vector<PlayerDefaultAttack*>::iterator iter;
	for (iter = defaultAttackVec.begin(); iter != defaultAttackVec.end(); iter++)
	{
		attack = *iter;
		attack->Fire(pos, level);
	}
}
