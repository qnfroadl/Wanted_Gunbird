#pragma once

#include <deque>
#include "config.h"




class ActionPattern
{
	bool isLoop;
	std::deque<FPOINT> posList;

public:
	void pushfront(FPOINT pos)
	{
		posList.push_front(pos);
	}

	void move()
	{
		if (isLoop)
		{
			FPOINT pos = posList.back();
			posList.pop_back();

			// move to pos, update

		}
		else return;
	}
};






