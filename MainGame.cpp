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
#include "StageManager.h"
#include "BackgroundUI.h"
#include "EffectManager.h"
#include "EnemyMissileManager.h"
#include "Item.h"

#include "ItemManager.h"

void MainGame::EffectSimulation()
{
	// test

	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F1))
	{
		EffectManager::GetInstance()->PlayEffect(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, EEffectType::ExplosionBig);
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F2))
	{
		EffectManager::GetInstance()->PlayEffect(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, EEffectType::ExplosionSmall);
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F3))
	{
		EffectManager::GetInstance()->PlayEffect(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, EEffectType::ExplosionPlayer);
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_F4))
	{
		EffectManager::GetInstance()->PlayEffect(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, EEffectType::ShotImpact);
	}

}

void MainGame::ItemSpawnSimulation()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(VK_LSHIFT))
	{
		ItemManager::GetInstance()->SpawnItem(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, ItemType::PowerUp);
	}
	else if (KeyManager::GetInstance()->IsOnceKeyDown(VK_RSHIFT))
	{
		ItemManager::GetInstance()->SpawnItem(FPOINT{ WINSIZE_X / 2,WINSIZE_Y / 2 }, ItemType::BombAdd);
	}
	
}

void MainGame::Init()
{
	CollisionManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ImageManager::GetInstance()->Init();
	EnemyMissileManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init();
	EffectManager::GetInstance()->Init();

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


	stageManager = new StageManager();
	stageManager->Init();

	/*enemyMissileManager = new EnemyMissileManager();
	enemyMissileManager->Init();*/

	backgroundUI = new BackgroundUI();
	backgroundUI->Init();

	// test
	stageManager->Start();

	ItemManager::GetInstance()->SpawnItem(FPOINT{200,200}, ItemType::BombAdd);
}

void MainGame::Release()
{
	CollisionManager::GetInstance()->Release();
	KeyManager::GetInstance()->Release();
	ImageManager::GetInstance()->Release();
	EnemyMissileManager::GetInstance()->Release();
	EnemyManager::GetInstance()->Release();
	EffectManager::GetInstance()->Release();

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

	if (stageManager)
	{
		stageManager->Release();
		delete stageManager;
		stageManager = nullptr;
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
	EnemyManager::GetInstance()->Update();
	backgroundUI->Update();
	player->Update();
	stageManager->Update();
	EffectManager::GetInstance()->Update();
	EnemyMissileManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();


	EffectSimulation();
	ItemSpawnSimulation();
}

void MainGame::Render()
{
	// 백버퍼에 먼저 복사
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backgroundUI->Render(hBackBufferDC);
	EnemyManager::GetInstance()->Render(hBackBufferDC);
	player->Render(hBackBufferDC);
	stageManager->Render(hBackBufferDC);
	ItemManager::GetInstance()->Render(hBackBufferDC);
	
	//enemyMissileManager->Render(hBackBufferDC);
	EnemyMissileManager::GetInstance()->Render(hBackBufferDC);
	EffectManager::GetInstance()->Render(hBackBufferDC);
	CollisionManager::GetInstance()->Render(hBackBufferDC);

	// wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	// TextOut(hBackBufferDC, 20, 60, szText, wcslen(szText));

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

