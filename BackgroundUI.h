#pragma once

#include "GameObject.h"
#include <array>
#define BACK_WIDTH 600
#define BACK_HEIGHT 1000

class Image;
class BackgroundUI : public GameObject
{
private:
	int life;
	int bomb;
	int score;
	float moveY;

	float speed;
	
	int bottomIndex;
	int topIndex;
	array< Image*, 2> loopBackground;
	
	Image* imageLife;
	Image* imageBomb;
	bool bFinal;

	wchar_t szText[10];
	wchar_t dTimeText[40];
public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void SetSpeed(float speed);
	void SetFinal(bool bFinal);
	void SetLife(int lifeCount);
	void SetBomb(int bombCount);
	void SetScore(int score);

};

