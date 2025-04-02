#include "MainGame.h"
#include "CommonFunction.h"
#include "Image.h"
#include "CollisionManager.h"
#include "ImageManager.h"
#include "Timer.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "Player.h"
#include "EnemyManager.h"
#include "BackgroundUI.h"
#include "EnemyMissileManager.h"
#include "Item.h"


void MainGame::Init()
{
	CollisionManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();
	EnemyMissileManager::GetInstance()->Init();

	FPS = 60;

	this->hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("백버퍼 생성 실패"), TEXT("경고"), MB_OK);
	}

	player = new Player();
	player->Init();

	enemyManager = new EnemyManager;
	enemyManager->Init();

	/*enemyMissileManager = new EnemyMissileManager();
	enemyMissileManager->Init();*/

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
	EnemyMissileManager::GetInstance()->Release();

	if (player)
	{
		player->Release();
		delete player;
		player = nullptr;
	}

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

	if (enemyManager)
	{
		enemyManager->Release();
		delete enemyManager;
		enemyManager = nullptr;
	}

	/*if (enemyMissileManager)
	{
		enemyMissileManager->Release();
		delete enemyMissileManager;
		enemyMissileManager = nullptr;
	}*/

	backgroundUI->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	CollisionManager::GetInstance()->Update();
	backgroundUI->Update();

	item->Update();

	CollisionManager::GetInstance()->Update();
	player->Update();

	enemyManager->Update();

	//enemyMissileManager->Update();

	EnemyMissileManager::GetInstance()->Update();
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backgroundUI->Render(hBackBufferDC);

	item->Render(hBackBufferDC);

	player->Render(hBackBufferDC);

	CollisionManager::GetInstance()->Render(hBackBufferDC);

	enemyManager->Render(hBackBufferDC);

	//enemyMissileManager->Render(hBackBufferDC);
	EnemyMissileManager::GetInstance()->Render(hBackBufferDC);

	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));


	// 백버퍼에 있는 내용을 메인 hdc에 복사
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

