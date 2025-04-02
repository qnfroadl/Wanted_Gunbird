#pragma once

#include "Item.h"
#include "Singleton.h"
#include <unordered_map>

// Ư�� ��ġ�� �������� �������ְ�, �Ҹ���� ���� ���ִ� Ŭ����.
class ItemManager : public Singleton<ItemManager>
{

private:
	unordered_set<Item*> items;

public:
	void Update();
	void Render(HDC hdc);
	void Release();

	void SpawnItem(const FPOINT& pos, ItemType type);
	
};