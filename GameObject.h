#pragma once
#include "config.h"
#include <unordered_set>

class GameObject
{
private:
	bool bActive;
	unordered_set<GameTag> tags;

public:
	virtual void Init();		// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위로 게임 로직 실행(데이터 계산)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)

	virtual void SetActive(bool _bActive);
	bool IsActive();

	GameObject();
	virtual ~GameObject();

	void AddTag(GameTag tag);
	void AddTags(const unordered_set<GameTag>& tags);
	const unordered_set<GameTag>& GetTags();
	bool FindTag(GameTag tag);
};

