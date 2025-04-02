#include "EffectManager.h"

#include "ImageManager.h"
#include "Image.h"

Effect::Effect()
	:image(nullptr), curFrame(0), skipFrame(5), elapsedFrame(0)
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
		elapsedFrame++;
		if (elapsedFrame % skipFrame == 0)
		{
			curFrame++;
		}
		
		int maxFrameX = image->GetMaxFrameX();
		if (maxFrameX < curFrame)
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
		if (curFrame <= maxFrameX)
		{
			image->FrameRender(hdc, pos.x,pos.y, curFrame, 1, false);
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
		L"assets/Sprites/Effects/PlayerExplosion.bmp", 253, 31, 9, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(EImageKey::ExplosionSmall,
		L"assets/Sprites/Effects/PlayerExplosion.bmp", 253, 31, 9, 1, true, RGB(255, 0, 255));

	// ImageManager::GetInstance()->AddImage(EImageKey::ExplosionBig,
	// 	L"assets/Sprites/Effects/PlayerExplosion.bmp", 253, 31, 9, 1, true, RGB(255, 0, 255));

	ImageManager::GetInstance()->AddImage(EImageKey::ExplosionBig, TEXT("assets/Sprites/Misc/pickup_bomb.bmp"), 216, 16, 8, 1, true, RGB(255, 0, 255));
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

void EffectManager::PlayEffect(const FPOINT& pos, EEffectType key)
{
	Effect* effect = new Effect();
	effect->Init();
	effect->SetPos(pos);
	effect->SetEffectKey(key);

	vecEffects.push_back(effect);
}