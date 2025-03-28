#pragma once
#include "config.h"
#include "GameObject.h"
#include <list>
#include <map>
#include <functional>
#include <unordered_set>
#include "Singleton.h"

enum class CollisionType
{
	RECT, ELLIPSE
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
		map<GameObject*, list<Collision*>> collisionMap;

		void CollisionDetect(list<Collision*>& colList1, list<Collision*>& colList2);
		void Detect(Collision* c1, Collision* c2);

	public:
		CollisionEllipse* CreateCollisionEllipse(GameObject* obj, int x, int y, int width, int height);
		CollisionRect* CreateCollisionRect(GameObject* obj, const RECT& rt);

		void DeleteCollision(Collision* coll);

		void Update() override;
		void Render(HDC hdc) override;
		void Release() override;
		void CollisionDetect();

		CollisionManager& operator =(CollisionManager&) = delete;
};

