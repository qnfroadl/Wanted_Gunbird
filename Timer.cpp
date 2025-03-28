#include "Timer.h"

void Timer::Init()
{
	bHardWare = false;
	timeScale = 0.f;			

	timeElapsed = 0.f;
	curTime = 0;		
	lastTime = 0;
	periodFrequency = 0;

	fpsTimeElapsed = 0.f;
	fpsFrameCount = 0;
	FPS = 0;

	// hHardware Ȯ��
	bHardWare = QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
	if (bHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*) &lastTime);
		timeScale = 1.0 / periodFrequency;
		
	}
	else 
	{
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

}

void Timer::Tick()
{
	// ���� �ð� ���.
	if (bHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	}
	else
	{
		curTime = timeGetTime();
	}

	timeElapsed = (curTime - lastTime) * timeScale;
	lastTime = curTime;

	// FPS ���.
	fpsTimeElapsed += timeElapsed;
	fpsFrameCount++;

	if (1 <= fpsTimeElapsed)
	{
		FPS = fpsFrameCount;
		fpsFrameCount = 0;
		fpsTimeElapsed = 0;
	}

}

float Timer::GetCurTime()
{
	__int64 __curTime;

	if (bHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&__curTime);
	}
	else
	{
		__curTime = timeGetTime();
	}

	return __curTime;
}

unsigned long Timer::GetFPS()
{
	return this->FPS;
}

float Timer::GetDeltaTime()
{
	return this->timeElapsed;
}
