#pragma once

#include "Item.h"
#include "Singleton.h"
#include <unordered_map>

// 특정 위치에 아이템을 생성해주고, 소멸까지 관리 해주는 클래스.
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