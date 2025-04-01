#pragma once
#include "config.h"
#include <vector>

class MissileManager
{
private:
	vector<class Missile*> vecMissiles;
	vector<Missile*>::iterator iterMissiles;

public:
	MissileManager();

	virtual ~MissileManager();
	
	void Fire(FPOINT pos, float angle, class MissileType* type);

	void Fire(FPOINT pos, class MissilePattern* pattern);
};

