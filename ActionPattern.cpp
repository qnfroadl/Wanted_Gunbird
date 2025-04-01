#include "ActionPattern.h"


ActionPattern::ActionPattern()
{
	isLoop = true;
	loopCount = 0;
	totalLoop = 0;

	posList.push_front(FPOINT{ 100, 100 });
	posList.push_front(FPOINT{ 500, 100 });

	dir = { 0.0f, 0.0f };
	
	speed = .0f;

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

void ActionPattern::setDir()
{
		origin = posList.back();
		posList.pop_back();
		
		dest = posList.back();
		posList.pop_back();
		
		dir.x = dest.x - origin.x;
		dir.y = dest.y - origin.y;
		dir.normalize();
}

VEC2 ActionPattern::move()
{	
	if (isLoop)  
		return dir * speed;	
	else 
		return VEC2{0.0f, 0.0f};
}
