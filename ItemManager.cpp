#include "ItemManager.h"

void ItemManager::Update()
{
	Item* item = nullptr;

	auto it = items.begin();
	while (it != items.end())
	{
		item = *it;
		if (item->IsActive())
		{
			item->Update();
		}
		else 
		{
			// 비활성화라면 죽어라.
			item->Release();
			delete item;
			it = items.erase(it);
			continue;
		}

		it++;
	}
}

void ItemManager::Render(HDC hdc)
{
	Item* item = nullptr;
	auto it = items.begin();
	
	while (it != items.end())
	{
		item = *it;
		if (item->IsActive())
		{
			item->Render(hdc);
		}
		it++;
	}
}

void ItemManager::Release()
{
	Item* item = nullptr;
	auto it = items.begin();

	while (it != items.end())
	{
		item = *it;
		item->Release();
		delete item;
		items.erase(it);
	}


	ReleaseInstance();

}

void ItemManager::SpawnItem(const FPOINT& pos, ItemType type)
{
	Item* item = new Item(type, 15);
	item->Init();
	item->SetPos(pos);
	items.insert(item);

}
