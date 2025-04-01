#include "MainGame.h"

#include "CommonFunction.h"
#include "Image.h"

#include "CollisionManager.h"
#include "ImageManager.h"
#include "Timer.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "BackgroundUI.h"

#include "Item.h"
void MainGame::Init()
{
	CollisionManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();

	FPS = 60;

	this->hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}

	backgroundUI = new BackgroundUI();
	backgroundUI->Init();

	KeyManager::GetInstance()->Init();
	
	item = new Item(ItemType::BombAdd);
	item->Init();

	item->SetPos(WINSIZE_X / 2, WINSIZE_Y / 2);
}

void MainGame::Release()
{
	CollisionManager::GetInstance()->Release();
	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
	
	if (backgroundUI)
	{
		backgroundUI->Release();
		delete backgroundUI;
		backgroundUI = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	backgroundUI->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	CollisionManager::GetInstance()->Update();
	KeyManager* keyManager = KeyManager::GetInstance();

	backgroundUI->Update();

	item->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	// ����ۿ� ���� ����
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backgroundUI->Render(hBackBufferDC);

	item->Render(hBackBufferDC);

	 CollisionManager::GetInstance()->Render(hBackBufferDC);
	// TimerManager::GetInstance()->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

	// ����ۿ� �ִ� ������ ���� hdc�� ����
	backBuffer->Render(hdc);

}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		//hTimer = (HANDLE)SetTimer(hWnd, 0, 10, NULL);

		break;
	case WM_TIMER:
		//this->Update();
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		mousePos.x = LOWORD(lParam);
		mousePos.y = HIWORD(lParam);

		break;
	case WM_PAINT:
		//hdc = BeginPaint(g_hWnd, &ps);

		//this->Render(hdc);

		//EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		//KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

