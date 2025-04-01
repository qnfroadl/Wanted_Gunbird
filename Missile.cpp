#include "Missile.h"
#include "Image.h"
#include "CollisionManager.h"

Missile::Missile()
{
	image = nullptr;
	damage = 1;
	speed = 5.0f;
	collision = nullptr;
}

Missile::~Missile()
{
	if (image)
	{
		image->Release();
		delete image;
		image = nullptr;
	}
}
