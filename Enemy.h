#pragma once

#include <bitset>
#include "config.h"
#include "GameActor.h"
#include <deque>
#include <vector>

class Enemy: public GameActor
{
	int score;
	int hp;
	class Image* image;
	float width, height;
	int animFrame;
	float speed;
	float elapsedTime;
	float fireTime;
	float firePeriod;
	class CollisionRect* collision;
	class ActionPattern* pattern;		
	std::deque<class MissilePattern*> missilePatterns;
	class EnemyMissileManager* enemyMissileManager;

public:
	Enemy(int hp)
	{
		score = 0;
		this->hp = hp;
		image = nullptr;
		width = 0;
		height = 0;
		animFrame = 0;
		speed = 0;
		elapsedTime = 0;
		fireTime = 0;
		firePeriod = 2.0;
		collision = nullptr;
		pattern = nullptr;
		enemyMissileManager = nullptr;
	};

	virtual ~Enemy() {};

	void Init(const string& key, const wchar_t* filePath, float width, float height,
		int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor);

	void setMissilePattern(int fireCount, float fireDelay, float speed, float angleMin, float angleMax);

	void Fire();

	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;

	void On_CollisionDetected(GameObject* obj);

	void Damaged(int damage);
	void Dead();

	inline ActionPattern* getPattern()
	{
		return pattern;
	}

	inline int getHp() { return hp; }
};

