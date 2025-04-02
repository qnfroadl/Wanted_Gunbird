#pragma once

#include "GameObject.h"
#include <deque>
#include "config.h"
class Image;
class ActionPattern;
class MissilePattern;

typedef struct _StageInfo
{
	bool deadCheck;						//�ռ� ������ ������ �׾����� üũ�� �ʿ��ϸ� true, �ƴϸ� false
	int stepTime;						//�ش� �ð��� ������ ���� ���ش�.
	FPOINT startPos;					//�� ���� ��ġ,
	int enemyType;						//�� ����
	int enemyCount;						//�� ��
	int spawnDelay;						//�� �������� ������ ������
	
}StageInfo;

class StageManager : public GameObject
{

private:
	int curStep;	// �������� ���� �ܰ�.
	deque<StageInfo> deqStageInfo;
	
	Image* stageAlert;		// ����Ʈ ����, ���� ������ ��� ����� �̹���
	int curFrame;
	int maxFrame;

	void LoadStageInfo();
	void StepCheck();

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	
	void Start();
	
	
};