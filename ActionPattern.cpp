#include "ActionPattern.h"
#include "Enemy.h"
#include "CommonFunction.h"


ActionPattern::ActionPattern(int paddingX,int paddingUpY,int paddingDownY)
{
	isLoop = true;
	isCurve = false;

	this->paddingX = paddingX;
	this->paddingUpY = paddingUpY;
	this->paddingDownY = paddingDownY;

	posList.push_back(FPOINT{ WINSIZE_X/2.0f, 200 });	// starting point
	posList.push_back(FPOINT{ 500, 200 });

	dir = { 0.0f, 0.0f };
	if (isCurve) dir.x = 1.0f;
	dirAccumulated = 0;

	speed = 1.0f;
	angle = 50.0f;

	randomStopFreq = 2;
	randomDirChange = 50; // change 1 out of randomDirChange

	origin = { 0.0f, 0.0f };
	dest = { 0.0f, 0.0f };

	setLinearDir();
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
		origin = posList[0];		
		dest = posList[1];

		dir.x = dest.x - origin.x;
		dir.y = dest.y - origin.y;
		dir.normalize();
}

void ActionPattern::setCurveDir()
{	
	angle++;
	//dir.x = cosf(DEG_TO_RAD(angle));
	//dir.y = sinf(DEG_TO_RAD(angle));
	 		
	dir.y = sinf(DEG_TO_RAD(angle));
}

VEC2 ActionPattern::move(const RECT& rt)
{	

	if (isLoop)  
	{
		// random pause
		if (std::rand() % randomStopFreq) return VEC2{ 0.0f, 0.0f };

		if (isCurve)
		{
			setCurveDir();
;		}

		// random direction change
		if (std::rand() % randomDirChange == 0)
		{
			dir = -dir;
		}

		// if it is out of the box
		if (IsOutofScreen(rt, paddingX, paddingUpY, paddingDownY))
		{	
			angle = angle + 45;
			dir = - dir;			
		}
		
		return dir * speed;		
	}
	else 
		return VEC2{0.0f, 0.0f};
}

