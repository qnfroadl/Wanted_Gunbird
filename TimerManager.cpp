#include "TimerManager.h"

#include "Timer.h"

void TimerManager::Init()
{
	timer = new Timer();
	timer->Init();
}

void TimerManager::Update()
{
	if (timer)
	{
		timer->Tick();

		elapsedTime += timer->GetDeltaTime();
	}
}

void TimerManager::Render(HDC hdc)
{
	wsprintf(szText, L"FPS: %d", timer->GetFPS());
	TextOut(hdc, WINSIZE_X - 100, 10, szText, wcslen(szText));
}

void TimerManager::Release()
{
	Singleton::ReleaseInstance();
}

unsigned long TimerManager::GetFPS()
{
	return timer->GetFPS();
}

float TimerManager::GetDeltaTime()
{
	return timer->GetDeltaTime();
}

bool TimerManager::GetFrame()
{
	if ( (1.f / maxFrame)  <= elapsedTime)
	{
		elapsedTime = 0;
		return true;
	}

	return false;
}

void TimerManager::SetMaxFrame(uint32_t _maxFrame)
{
	this->maxFrame = _maxFrame;
}
