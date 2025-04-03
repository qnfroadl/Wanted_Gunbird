#include "StageManager.h"

// #include "EnemyManager.h"
#include "Timer.h"
#include "ImageManager.h"
#include "Image.h"
#include <fstream>
#include <sstream>
#include "EnemyManager.h"

void StageManager::LoadStageInfo()
{
	StageInfo info;
	int stepCount;

	ifstream file("Data/StageInfo.dat");  // ���� �̸�
	if (!file.is_open()) 
	{
		MessageBox(g_hWnd, TEXT("�������� ���� �б� ����"), TEXT("���"), MB_OK);
		return;
	}

	string line;
	if (getline(file, line))
	{
		stringstream ss(line);
		ss >> stepCount;

		for (int i = 0; i < stepCount; i++)
		{
			if (getline(file, line))
			{
				stringstream sInfo(line);
				sInfo >> info.deadCheck >> info.stepTime >> info.startPos.x >> info.startPos.y
					>> info.enemyType >> info.enemyCount >> info.spawnDelay;

				deqStageInfo.push_back(info);
			}
		}
	}

	file.close();
}

void StageManager::StepCheck()
{
	if (deqStageInfo.size() <= curStep && curStep < deqStageInfo.size())
	{
		deqStageInfo[curStep];




	}
	
}

void StageManager::Init()
{
	curStep = -1;
	LoadStageInfo();
	stageAlert = nullptr;
	curFrame = 0;
	maxFrame = 0;

}

void StageManager::Update()
{
	if (0 <= curStep)
	{
		StepCheck();
	}
}

void StageManager::Render(HDC hdc)
{
	if (nullptr != stageAlert)
	{
		stageAlert->Render(hdc);
	}
}

void StageManager::Release()
{
	curStep = -1;

}

void StageManager::Start()
{
	curStep = 0;



	// test
	// EnemyManager::GetInstance()->SpawnEnemy(FPOINT{200,200}, 0);
}
