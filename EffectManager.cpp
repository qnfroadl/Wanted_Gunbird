#include "EffectManager.h"

#include "ImageManager.h"
#include "Image.h"

Effect::Effect()
	:image(nullptr), curFrame(0), skipFrame(5)
{
	
}

void Effect::SetEffectKey(EEffectType key)
{
	image = ImageManager::GetInstance()->FindImage((EImageKey)key);
}

void Effect::Update()
{
	if (nullptr != image)
	{
		curFrame++;
		
		if (image->GetMaxFrameX() <= curFrame/skipFrame)
		{
			image = nullptr;
			SetActive(false);
		}
	}
}

void Effect::Render(HDC hdc)
{
	if (nullptr != image)
	{
		const FPOINT& pos = GetPos();

		int maxFrameX = image->GetMaxFrameX();
		if (curFrame / skipFrame <= maxFrameX)
		{
			image->FrameRender(hdc, pos.x,pos.y, curFrame / skipFrame, 0, false);
		}
	}
}

void Effect::SetSkipFrame(int skipFrame)
{
	this->skipFrame = skipFrame;
}

void EffectManager::Init()
{
	vecEffects.reserve(100);

	// 이펙트들 추가 할 예정
	ImageManager::GetInstance()->AddImage(EImageKey::ExplosionPlayer,
		L"assets/Sprites/Effects/PlayerExplosion.bmp", 279, 31, 9, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(EImageKey::ExplosionSmall,
		L"assets/Sprites/Effects/PlayerExplosion.bmp", 279, 31, 9, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(EImageKey::ExplosionBig,
		L"assets/Sprites/Effects/PlayerExplosion.bmp", 279, 31, 9, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(EImageKey::ShotImpact,
		L"assets/Sprites/Effects/ShotImpact.bmp", 255, 42, 17, 1, true, RGB(255, 0, 255));
}

void EffectManager::Update()
{
	Effect* effect = nullptr;
	
	auto it = vecEffects.begin();
	while (it != vecEffects.end())
	{
		effect = (*it);
		if (effect->IsActive())
		{
			effect->Update();
		}
		else 
		{
			effect->Release();
			delete effect;
			
			it = vecEffects.erase(it);
			continue;
		}
		it++;
	}


}

void EffectManager::Render(HDC hdc)
{
	Effect* effect = nullptr;

	auto it = vecEffects.begin();
	while (it != vecEffects.end())
	{
		effect = (*it);
		if (effect->IsActive())
		{
			effect->Render(hdc);
		}
		it++;
	}
}

void EffectManager::Release()
{
	Effect* effect = nullptr;
	
	auto it = vecEffects.begin();
	while (it != vecEffects.end())
	{
		effect = (*it);
		effect->Release();
		delete effect;

		it++;
	}

	vecEffects.clear();

	ReleaseInstance();
}
#include "ItemManager.h"

void EffectManager::PlayEffect(const FPOINT& pos, EEffectType key)
{
	Effect* effect = new Effect();
	effect->Init();
	effect->SetPos(pos);
	effect->SetEffectKey(key);
	
	vecEffects.push_back(effect);
}