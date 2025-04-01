#pragma once
#include "config.h"

class MissilePattern
{
private:
	FPOINT startPoint;
	int firecount;
	float fireDelay;
	class MissileType* type;
	float angleMin;
	float angleMax;

public:
	MissilePattern() {
		startPoint = { 0.0f, 0.0f };
	};

	virtual ~MissilePattern() {};

	FPOINT getStartPoint();

	void move();
};

