#pragma once
#include "GameObject.h"

class Image;
class Timer;
class Player;
class BackgroundUI;
class Item;
class StageManager;
class BossShip;
class BossBird;
class MainGame : public GameObject
{
private:
	Image* backBuffer;
	HDC hdc;
	PAINTSTRUCT ps;
	//HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	
	FPOINT mousePos;
	wchar_t szText[128];

	int FPS;
	Player* player;
	int playerLife;
	BackgroundUI* backgroundUI;
	StageManager* stageManager;

	BossShip* canon;
	BossBird* bird;

	// 콜리젼매니저 체크용
	int collCount;
	int activeCollCount;
	int collCheckCount;

	void UpdateCollisionPerformance();
	void EffectSimulation();
	void ItemSpawnSimulation();

public:
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
					// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();

	inline int GetFPS() { return this->FPS; }
};

