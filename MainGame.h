#pragma once
#include "GameObject.h"

class Image;
class Timer;
class BackgroundUI;

class Item;
class MainGame : public GameObject
{
private:
	int FPS;

	HDC hdc;
	PAINTSTRUCT ps;
	//HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	
	FPOINT mousePos;
	wchar_t szText[128];

	Image* backBuffer;
	BackgroundUI* backgroundUI;


	// test
	Item* item;
public:
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
					// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();

	inline int GetFPS() { return this->FPS; }
};

