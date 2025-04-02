#pragma once
#include <unordered_set>
#include "Singleton.h"
#include "config.h"
#include "GameActor.h"

class Image;

class Effect : public GameActor
{
private:
	Image* image;
	int curFrame;

public:
	void SetEffectKey(EEffectType key);
	void Update();
	void Render();

};


class EffectManager : public Singleton<EffectManager>
{

private:
	std::unordered_set<Image*> setImages;

public:
	void Init();
	void Update();
	void Render();
	void Release();

	void PlayEffect(const FPOINT& pos, EEffectType key);

};

