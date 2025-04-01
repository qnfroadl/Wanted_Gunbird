#pragma once


class Missile
{
private:
	class Image* image;
	float speed;
	int damage;
	class CollisionRect* collision;

public:
	Missile();

	virtual ~Missile();


	

};

