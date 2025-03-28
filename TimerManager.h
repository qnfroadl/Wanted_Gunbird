#pragma once

#include "Singleton.h"
#include "config.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{

private:
	Timer* timer;
	wchar_t szText[10];

	uint32_t maxFrame;
	float elapsedTime;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	unsigned long GetFPS();
	float GetDeltaTime();

	bool GetFrame();
	void SetMaxFrame(uint32_t maxFrame);	// 최대 프레임 설정.
	
};

