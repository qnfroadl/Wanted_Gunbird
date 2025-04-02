// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include "KeyManager.h"

using namespace std;

/*
	�����Ϸ����� �ش� �ڵ带 �ڿ� ���ǵ� �ڵ�� �����Ѵ�. 
*/
#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

enum class GameTag
{
	PowerUp, BombUp, Player, Enemy, EliteEnemy, BossEnemy, 
};

enum class EImageKey
{
	Player,

};

typedef struct vector2d {
	float x, y;

	float length() const {
		return std::sqrt(x * x + y * y);
	}

	void normalize() {
		float len = length();
		if (len > 0)
		{
			x /= len;
			y /= len;
		}
	}

	vector2d operator*(float mul)
	{
		return vector2d{ x * mul, y * mul };
	}

	vector2d operator-()
	{
		x = -x;
		y = -y;
		return vector2d{ x, y };
	}
} VEC2;


typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

typedef struct missileInfo {
	FPOINT startPos;
	float fireDelay;
	float speed;
	float angle;
} MissileInfo;

typedef struct _Ellipse
{
	int centerX;
	int centerY;
	int width;
	int height;
} CEllipse;

/*
	extern Ű���� : ������ �Լ��� �ٸ� ���Ͽ� ���ǵǾ� �ִ� ���
	����� �˸��� Ű����.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
