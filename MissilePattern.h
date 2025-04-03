#pragma once
#include "config.h"
#include <vector>

class MissilePattern
{
private:
	FPOINT startPos;
	int fireCount;
	float fireDelay;
	float speed;
	class MissileType* type;
	float angleMin;
	float angleMax;
	float accumulatedTime;

public:
	MissilePattern();

	virtual ~MissilePattern() {};

	void Init(FPOINT startPos, int fireCount, float fireDelay, float speed, float angleMin, float angleMax);

	FPOINT getStartPoint();

	std::vector<SpawnMissileInfo> getMissilesInfo();
};

