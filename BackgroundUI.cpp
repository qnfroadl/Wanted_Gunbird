#include "BackgroundUI.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"
void BackgroundUI::Init()
{
	imageBackground = ImageManager::GetInstance()->AddImage("Background", TEXT("assets/LevelBackgrounds/bg_castle.bmp"), BACK_WIDTH, BACK_HEIGHT);
	imageLife = ImageManager::GetInstance()->AddImage("Life", TEXT("assets/UI/UI Backgrounds/life.bmp"), 13, 13, true, RGB(255, 0, 255));
	imageBomb = ImageManager::GetInstance()->AddImage("Bomb", TEXT("assets/UI/UI Backgrounds/bomb.bmp"), 28, 16, true, RGB(255, 0, 255));

	// test code
	life = 3;
	bomb = 4;
	speed = 20;
}

void BackgroundUI::Release()
{
	
}

void BackgroundUI::Render(HDC hdc)
{
	if (imageBackground)
	{
		float multiple = WINSIZE_X / (float)BACK_WIDTH;
		imageBackground->RenderStretch(hdc, BACK_WIDTH * multiple, WINSIZE_Y * multiple);
	}
	for (int i = 0; i < life; i++)
	{
		imageLife->RenderCenter(hdc, WINSIZE_X - 500 + (i * 20), WINSIZE_Y - 20);
	}
	for (int i = 0; i < bomb; i++)
	{
		imageBomb->RenderCenter(hdc, WINSIZE_X - 200 + (i * 30), WINSIZE_Y - 20);
	}

	TextOut(hdc, WINSIZE_X - 100, 10, szText, wcslen(szText));
	TextOut(hdc, WINSIZE_X - 130, 25, dTimeText, wcslen(dTimeText));
}

void BackgroundUI::Update()
{
	curFrame++;

	if (WINSIZE_Y <= curFrame)
	{
		curFrame = 0;
	}

	int gameFrame = TimerManager::GetInstance()->GetFPS();
	wsprintf(szText, L"FPS: %d", gameFrame);

	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	swprintf_s(dTimeText, L"deltaTime: %.5f", deltaTime);
}

void BackgroundUI::SetSpeed(float speed)
{
	this->speed = speed;
}

void BackgroundUI::SetLife(int lifeCount)
{
	this->life = lifeCount;
}

void BackgroundUI::SetBomb(int bombCount)
{
	this->bomb = bombCount;
}

void BackgroundUI::SetScore(int score)
{
	this->score = score;
}
