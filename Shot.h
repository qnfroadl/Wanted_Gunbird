#pragma once

#include "GameActor.h"
class Image;
class CollisionRect;
class Shot : public GameActor
{

private:
	Image* shotImage;
	int width;
	int height;

	float speed;
	float angle;
	int curFrame;

	CollisionRect* collision;
	
	void Move();
	void On_CollisionDetected(GameObject* obj);

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc);
	void Release();

	void Fire(const FPOINT& pos, float angle);
	void SetActive(bool bActive) override;

	void SetShotImage(EImageKey key, const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY, bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void SetSpeed(float speed);
};

