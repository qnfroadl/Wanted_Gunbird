// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include "KeyManager.h"
#include <unordered_map>

using namespace std;

/*
	컴파일러에서 해당 코드를 뒤에 정의된 코드로 변경한다. 
*/
#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

enum class EEnemyType
{
	FlyingEnemy,
	MidBoss,
};

enum class GameTag
{
	PowerUp, BombUp, Player, PlayerDefaultAttack, PlayerMissileAttack, Enemy, EliteEnemy, BossEnemy, PlayerBomb,
	Boss_Canon, Shot,
};

enum class EImageKey
{
	Player,
	PickupBomb,PickupPower,
	PlayerAttackDefault,
	PlayerAttackMissile,
	CanonShot,

	// 캐논 각도별 이미지
	Canon_210, Canon_250, Canon_270, Canon_290, Canon_330,

	// Boss_Ship
	ShipBase, ShipDestroyedLeft, ShipDestroyedRight, ShipDestroyed,
	PlayerBomb,

	// 하단의 Effect 종류들은 FindImage로 찾아서 쓰기만 하면됩니다.
	ExplosionPlayer, ExplosionSmall, ExplosionBig, ShotImpact,

	// Enemy
	FlyingEnemy, MidBossBasic, MidBossUpgrade,

	// Missile
	MidBossStar, MidBossPyramid,
};

typedef struct EnemyInformation {
	EImageKey key;
	const wchar_t* filePath;
	int hp;
	float width;
	float height;
	int maxFrameX;
	int maxFrameY;
	bool isTransparent;
	COLORREF transColor;
} EnemyImgInfo;

typedef struct MissileImageInformation {
	EImageKey key;
	const wchar_t* filePath;	
	float width;
	float height;
	int maxFrameX;
	int maxFrameY;
	bool isTransparent;
	COLORREF transColor;
} MissileImgInfo;

enum class EEffectType
{
	ExplosionPlayer = EImageKey::ExplosionPlayer,
	ExplosionSmall= EImageKey::ExplosionSmall,
	ExplosionBig = EImageKey::ExplosionBig,
	ShotImpact = EImageKey::ShotImpact,
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

typedef struct SpawnMissileInformation {
	EImageKey key;
	FPOINT startPos;
	float fireDelay;
	float speed;
	float angle;
} SpawnMissileInfo;

typedef struct _Ellipse
{
	int centerX;
	int centerY;
	int width;
	int height;
} CEllipse;

/*
	extern 키워드 : 변수나 함수가 다른 파일에 정의되어 있다 라는
	사실을 알리는 키워드.
*/
extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
