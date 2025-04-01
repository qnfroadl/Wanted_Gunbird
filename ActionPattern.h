#pragma once

#include <deque>
#include "config.h"


class ActionPattern
{
	bool isLoop;
	int loopCount;
	int totalLoop;

	std::deque<FPOINT> posList;

	VEC2 dir;
	float speed;
	
	FPOINT origin;
	FPOINT dest;

public:
	ActionPattern();

	virtual ~ActionPattern();

	void pushfront(FPOINT pos);	

	void setDir();

	VEC2 move();

	inline void setSpeed(float speed) {
		this->speed = speed;
	}

};

