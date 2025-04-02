#pragma once

#include "GameObject.h"
#include <deque>
#include "config.h"
class Image;
class ActionPattern;
class MissilePattern;

typedef struct _StageInfo
{
	bool deadCheck;						//앞서 스폰된 적들이 죽었는지 체크가 필요하면 true, 아니면 false
	int stepTime;						//해당 시간이 지나면 스폰 해준다.
	FPOINT startPos;					//적 스폰 위치,
	int enemyType;						//적 종류
	int enemyCount;						//적 수
	int spawnDelay;						//적 여러마리 스폰시 딜레이
	
}StageInfo;

class StageManager : public GameObject
{

private:
	int curStep;	// 스테이지 진행 단계.
	deque<StageInfo> deqStageInfo;
	
	Image* stageAlert;		// 엘리트 출현, 보스 출현시 경고 띠용띠용 이미지
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