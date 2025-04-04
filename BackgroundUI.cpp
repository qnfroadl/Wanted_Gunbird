#include "BackgroundUI.h"
#include "ImageManager.h"
#include "Image.h"
#include "TimerManager.h"

#define RATIO 1.5
void BackgroundUI::Init()
{
	ImageManager::GetInstance()->AddImage(EImageKey::BG_SeaBottom, TEXT("assets/UI/UI Backgrounds/background_1.bmp"), BACK_WIDTH, BACK_HEIGHT);
	ImageManager::GetInstance()->AddImage(EImageKey::BG_SeaLoop, TEXT("assets/UI/UI Backgrounds/background_2.bmp"), BACK_WIDTH, BACK_HEIGHT);
	
	imageLife = ImageManager::GetInstance()->AddImage("Life", TEXT("assets/UI/UI Backgrounds/life.bmp"), 13 * RATIO, 13 * RATIO, true, RGB(255, 0, 255));
	imageBomb = ImageManager::GetInstance()->AddImage("Bomb", TEXT("assets/UI/UI Backgrounds/bomb.bmp"), 28 * RATIO, 16 * RATIO, true, RGB(255, 0, 255));

	life = 3;
	bomb = 4;
	speed = 40;
	moveY = 0;

	topIndex = 1;
	bottomIndex = 0;
	bFinal = false;

	loopBackground[topIndex] = ImageManager::GetInstance()->FindImage(EImageKey::BG_SeaLoop);
	loopBackground[topIndex] = ImageManager::GetInstance()->FindImage(EImageKey::BG_SeaBottom);
}

void BackgroundUI::Update()
{
	moveY += speed * TimerManager::GetInstance()->GetDeltaTime();

	if (WINSIZE_Y <= moveY)
	{
		moveY = 0;
	}

	int gameFrame = TimerManager::GetInstance()->GetFPS();
	wsprintf(szText, L"FPS: %d", gameFrame);

	float deltaTime = TimerManager::GetInstance()->GetDeltaTime();
	swprintf_s(dTimeText, L"deltaTime: %.5f", deltaTime);
}

void BackgroundUI::Render(HDC hdc)
{
	loopBackground[topIndex]->Render(hdc, 0, -WINSIZE_Y + moveY);
	loopBackground[topIndex]->Render(hdc, 0, moveY);

	for (int i = 0; i < life; i++)
	{
		imageLife->RenderCenter(hdc, WINSIZE_X - 500 + (i * 20 * RATIO), WINSIZE_Y - 20);
	}
	for (int i = 0; i < bomb; i++)
	{
		imageBomb->RenderCenter(hdc, WINSIZE_X - 200 + (i * 30 * RATIO), WINSIZE_Y - 20);
	}

	TextOut(hdc, WINSIZE_X - 100, 10, szText, wcslen(szText));
	TextOut(hdc, WINSIZE_X - 130, 25, dTimeText, wcslen(dTimeText));
}



void BackgroundUI::SetSpeed(float speed)
{
	this->speed = speed;
}

void BackgroundUI::SetFinal(bool bFinal)
{
	this->bFinal = bFinal;
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
