#include "ActionPattern.h"
#include "Enemy.h"
#include "CommonFunction.h"


ActionPattern::ActionPattern(int paddingX,int paddingUpY,int paddingDownY)
{
	isLoop = true;
	isCurve = false;
	isRight = false;

	this->paddingX = paddingX;
	this->paddingUpY = paddingUpY;
	this->paddingDownY = paddingDownY;

	dir = { 0.0f, 0.0f };
	dirAccumulated = 0;

	speed = 1.0f;
	angle = 50.0f;

	randomStopFreq = 2;
	randomDirChange = 50; // change 1 out of randomDirChange

	origin = { 0.0f, 0.0f };
	dest = { 0.0f, 0.0f };
}

ActionPattern::~ActionPattern()
{
}

void ActionPattern::pushfront(FPOINT pos)
{
	posList.push_front(pos);			
}

FPOINT ActionPattern::getStartPoint()
{
	origin = posList.front();
	return origin;
}

void ActionPattern::setLinearDir()
{
		dir.x = 1.0f;
		dir.y = 0.0f;
		dir.normalize();
}

void ActionPattern::setCurveDir()
{	
	angle++; 		
	if (isRight)
	{
		dir.x = -cosf(DEG_TO_RAD(angle));
	}
	else
	{
		dir.x = cosf(DEG_TO_RAD(angle));
	}

	dir.y += 0.02f;
}

VEC2 ActionPattern::move(const RECT& rt)
{	

	if (isLoop)  
	{
		if (isCurve)
		{
			setCurveDir();
		}
		else			// random pause
		{
			if (std::rand() % randomStopFreq) return VEC2{ 0.0f, 0.0f };
		}

		// in linear movement, random direction change
		if (std::rand() % randomDirChange == 0 && isCurve == false)
		{
			dir = -dir;
		}
		
		return dir * speed;		
	}
	else 
		return VEC2{0.0f, 0.0f};
}

