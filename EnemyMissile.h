#pragma once
#include <deque>
#include "GameActor.h"
#include <memory>

class EnemyMissile: public GameActor
{
private:
	class Image* image;
	float speed;
	int damage;
	float width, height;
	float elapsedTime;
	class CollisionRect* collision;
	float angle;
	int animFrame;

public:
	EnemyMissile(float speed, float angle);

	virtual ~EnemyMissile();

	void Init(EImageKey key, const wchar_t* filePath, FPOINT startingPos, float width,
		float height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor);

	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	const RECT & getRect();

	void On_CollisionDetected(GameObject* obj);

};

