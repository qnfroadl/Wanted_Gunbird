#pragma once

#include "Singleton.h"
#include "config.h"
#include <vector>

class Shot;
class ShotManager : public Singleton<ShotManager>
{

private:
	std::vector<Shot*>::iterator curIt;
	std::vector<Shot*> vecShots;
	std::vector<Shot*> activeShots;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void ClearAllShot();
	void Fire(float x, float y, float angle, float speed);
	void Fire(const FPOINT& pos, float angle, float speed);

};

