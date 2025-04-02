#pragma once
#include <deque>
#include "GameActor.h"


class EnemyMissile: public GameActor
{
private:
	class Image* image;
	float speed;
	int damage;
	class CollisionRect* collision;
	class MissilePattern* pattern;
	int animFrame;

public:
	EnemyMissile();

	virtual ~EnemyMissile();

	void Init(const string& key, const wchar_t* filePath, float width, float height,
		int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor);
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void On_CollisionDetected(GameObject* obj);

};

