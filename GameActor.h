#pragma once

#include "GameObject.h"
#include "config.h"

class GameActor : public GameObject
{
	
private:
	
	FPOINT pos;

public:
	GameActor();
	virtual ~GameActor();

	const FPOINT& GetPos();

	virtual void SetPos(const float& x, const float& y);
	virtual void SetPos(const FPOINT& pos);

	virtual void AddPos(const float& x, const float& y);
	virtual void AddPos(const FPOINT& pos);

};