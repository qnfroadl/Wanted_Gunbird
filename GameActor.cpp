#include "GameActor.h"

GameActor::GameActor()
{
	
}

GameActor::~GameActor()
{

}

const FPOINT& GameActor::GetPos()
{
	return this->pos;
}

void GameActor::SetPos(const float& _x, const float& _y)
{
	this->pos.x = _x;
	this->pos.y = _y;
}

void GameActor::SetPos(const FPOINT& _pos)
{
	this->pos = _pos;
}

void GameActor::AddPos(const float& _x, const float& _y)
{
	this->pos.x += _x;
	this->pos.y += _y;
}

void GameActor::AddPos(const FPOINT& _pos)
{
	AddPos(_pos.x, _pos.y);
}