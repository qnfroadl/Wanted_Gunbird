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
	int elapsedFrame;
	int curFrame;
	int skipFrame;

public:
	Effect();
	void SetEffectKey(EEffectType key);
	void Update();
	void Render(HDC hdc);

	void SetSkipFrame(int skipFrame);

};

class EffectManager : public Singleton<EffectManager>
{

private:
	std::vector<Effect*> vecEffects;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void PlayEffect(const FPOINT& pos, EEffectType key);
};