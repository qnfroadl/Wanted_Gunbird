#pragma once

#include "GameObject.h"

#define BACK_WIDTH 228
#define BACK_HEIGHT 2108

class Image;
class BackgroundUI : public GameObject
{
private:
	int life;
	int bomb;
	int score;
	int curFrame;

	float speed;
	
	Image* imageBackground;
	Image* imageLife;
	Image* imageBomb;

	wchar_t szText[10];
	wchar_t dTimeText[40];
public:
	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();

	void SetSpeed(float speed);

	void SetLife(int lifeCount);
	void SetBomb(int bombCount);
	void SetScore(int score);
	
};

