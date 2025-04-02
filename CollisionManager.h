#pragma once
#include "config.h"
#include "GameObject.h"
#include <list>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include "Singleton.h"

enum class CollisionType
{
	RECT, ELLIPSE
};

enum class CollisionLayer : uint8_t
{
	Player = 1,				// 00000001
	PlayerAttack = 1 << 1,	// 00000010
	Enemy = 1 << 2,			// 00000100
	EnemyAttack = 1 << 3,	// 00001000
	Item = 1 << 4,			// 00010000
};


class Collision : public GameObject
{

private:
	GameObject* obj;
	bool bActive;
	std::function<void(GameObject* obj)> detection;
	CollisionType type;
	unordered_set<wstring> tags;

public:
	Collision(){}
	virtual ~Collision(){}

	void Bind(std::function<void(GameObject* obj)> func)
	{
		detection = func;
	}
	
	void SetActive(bool bActive);
	bool GetActive();

	void SetGameObject(GameObject* obj);
	GameObject* GetGameObject();

	CollisionType GetType();
	void SetType(CollisionType type);

	virtual void AddPos(float x, float y) = 0;

	friend class CollisionManager;
	
};

class CollisionRect : public Collision
{
private:
	RECT ctRect;
		
public:
	CollisionRect();

	const RECT& GetRect();
	void SetRect(const RECT& rt);
	void Render(HDC hdc) override;

	void AddPos(float x, float y) override;

};

class CollisionEllipse : public Collision
{
private:
	CEllipse ellipse;

public:
	CollisionEllipse();
	void SetEllipse(int x, int y, int width, int height);
	CEllipse GetEllipse();
	void Render(HDC hdc) override;

	void AddPos(float x, float y) override;

};

// CollisionManager
class CollisionManager : public Singleton<CollisionManager>, public GameObject
{
	private:
	
		unordered_map<GameObject*, list<Collision*>> collisionMap;

		unordered_map<CollisionLayer, std::pair<GameObject*, list<Collision*>>> layerMap;
		unordered_map<CollisionLayer, uint8_t> layerMaskMap;

		void CollisionDetect(list<Collision*>& colList1, list<Collision*>& colList2);
		void Detect(Collision* c1, Collision* c2);
		HBRUSH brush;
		HPEN pen;
	public:
		CollisionEllipse* CreateCollisionEllipse(GameObject* obj, int x, int y, int width, int height);
		CollisionRect* CreateCollisionRect(GameObject* obj, const RECT& rt);

		void DeleteCollision(Collision* coll);

		void Init() override;
		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
		void CollisionDetect();

		CollisionManager& operator =(CollisionManager&) = delete;
};

