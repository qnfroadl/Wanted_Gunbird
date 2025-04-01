#pragma once

#include "GameObject.h"

class StageManager : public GameObject
{

private:
	
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	
	void Start();
		
};

