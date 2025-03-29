#pragma once

#include <bitset>
#include "config.h"
#include "GameActor.h"
#include <deque>


class Enemy: public GameActor
{
	int score;
	int hp;
	class Image* image;
	int animFrame;
	float speed;
	float elapsedTime;
	class Collision* collision;
	class ActionPattern* pattern;
	class MissileManager* missileManager;
	std::deque<class MissilePattern*> missilePattern;

public:
	Enemy(int hp)
	{
		score = 0;
		this->hp = hp;
		image = nullptr;
		animFrame = 0;
		speed = 0;
		elapsedTime = 0;
		collision = nullptr;
		pattern = nullptr;
		missileManager = nullptr;
	};

	virtual ~Enemy() {};

	void Init(const string& key, const wchar_t* filePath, float width, float height,
		int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor);

	void Update() override;
	void Render(HDC hdc) override;

	ActionPattern* getPattern()
	{
		return pattern;
	}
};

