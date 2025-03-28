#pragma once
#include "config.h"
#include <unordered_set>

class GameObject
{
private:
	bool bActive;
	unordered_set<wstring> tags;

public:
	virtual void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ������ ���� ���� ����(������ ���)
	virtual void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	virtual void SetActive(bool _bActive);
	bool IsActive();

	GameObject();
	virtual ~GameObject();

	void AddTag(const wstring& tag);
	void AddTags(const unordered_set<wstring> tags);
	const unordered_set<wstring>& GetTags();
};

