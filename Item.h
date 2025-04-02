#pragma once

#include "GameActor.h"

class Image;
class CollisionRect;
enum class ItemType 
{
	PowerUp, BombAdd,
};

class Item : public GameActor
{
	
private:
	int width;
	int height;
	int curFrame;

	ItemType type;
	Image* image;
	CollisionRect* collision;

	int angle;	// 45도로 시작해서, 벽에 충돌 할 떄 마다 90도씩 추가해줘
	float speed;	// 아이템의 이동속도.

	int lifeTime;

public:
	Item(ItemType type, int lifeTime);
	~Item();
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void On_CollisionDetected(GameObject* obj);
	void MoveInWindow();

	void SetLifeTime(int lifeTime);
	void SetItemType(ItemType type);
};