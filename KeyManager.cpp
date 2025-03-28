#include "KeyManager.h"

HRESULT KeyManager::Init()
{
	keyUp.set();		// true�� ����.
	keyDown.reset();	// false�� ����.

	return S_OK;
}

void KeyManager::Release()
{
	Singleton::ReleaseInstance();
}

bool KeyManager::IsOnceKeyDown(int key)
{
	// �Լ� ȣ�� ������ ����Ű VK_??? �� � �������� Ȯ��.
	// 1. 0x0000: ���� �����ӿ� �������� ���� ȣ�� �������� �������� ����.
	// 2. 0x0001: ���� �����ӿ� �������� �ְ�, ȣ�� �������� �������� ����.
	// 3. 0x8000: ���� �����ӿ� �������� ����, ȣ�� �������� ��������.
	// 4. 0x8001: ���� �����ӿ� �������� �ְ�, ȣ�� �������� ��������.
	
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// ���� �����ִ�.
		if (false == keyDown[key])
		{
			keyDown[key] = true;
			return true;
		}
	}
	else 
	{
		keyDown[key] = false;
	}

	return false;
}

bool KeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		keyUp[key] = false;
		return false;
	}
	
	keyUp[key] = true;
	return true;
	
	
	

	// if (false == IsOnceKeyDown(key))
	// {
	// 	keyUp[key] = true;
	// 	return true;
	// }
	// 	
	// keyUp[key] = false;
	// return false;
}

bool KeyManager::IsStayKeyDown(int key)
{

	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	
	return false;
}
