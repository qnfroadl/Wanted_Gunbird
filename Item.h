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

	int angle;	// 45���� �����ؼ�, ���� �浹 �� �� ���� 90���� �߰�����
	float speed;	// �������� �̵��ӵ�.

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