#pragma once

#include <deque>
#include "config.h"

class ActionPattern
{
	bool isLoop;
	bool isCurve;
	bool isRight;

	int paddingX;
	int paddingUpY;
	int paddingDownY;

	int randomStopFreq;
	int randomDirChange;

	std::deque<FPOINT> posList;

	VEC2 dir;
	int dirAccumulated;
	float speed;
	float angle;
	
	FPOINT origin;
	FPOINT dest;

public:
	ActionPattern(
		int paddingX,
		int paddingUpY,
		int paddingDownY);

	virtual ~ActionPattern();

	void pushfront(FPOINT pos);	

	FPOINT getStartPoint();

	void setLinearDir();

	inline void setIsRight() { isRight = true; };

	void setCurveDir();

	// Bounding Box �ȿ��� �۵� ����
	// Random Timer�� random �ϰ� ���߱� ����
	// cos, sin �̿��� � ���, ���� ���� ����
	// ������ ��� ����

	VEC2 move(const RECT& rt);

	inline void setSpeed(float speed) {
		this->speed = speed;
	}

	inline void setIsCurve(bool isCurve) { this->isCurve = isCurve; }
};