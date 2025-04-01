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

public:
	Item(ItemType type);
	~Item();
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void On_CollisionDetected(GameObject* obj);
	void MoveInWindow();
};