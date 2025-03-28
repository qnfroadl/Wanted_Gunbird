#pragma once

#include "config.h"
#pragma comment(lib, "Winmm.lib")

class Timer
{

private:
	bool bHardWare;				// ���� Ÿ�̸Ӹ� ����� �� �ִ��� ����?
	float timeScale;			// ��� �������� �ʴ� �������� ������ �������� �ð����� ȯ���ϱ� ���� ��
	
	float timeElapsed;			// �ð� ����
	__int64 curTime;			// ���� �ð�.
	__int64 lastTime;			// ���� �ð�.
	__int64 periodFrequency;	// ���� Ÿ�̸� ���ļ� (�ʴ� ������)

	float fpsTimeElapsed;		// ������ ��� �ð�.
	unsigned long fpsFrameCount;// �ʴ� ������.
	unsigned long FPS;			// ?

public:
	void Init();
	void Tick();	// updateó�� �� ������ ȣ�� �������.
	float GetCurTime();

	unsigned long GetFPS();
	float GetDeltaTime();
};

