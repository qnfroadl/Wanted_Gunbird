#include "CollisionManager.h"
#include "CommonFunction.h"

void Collision::SetGameObject(GameObject* obj)
{
    this->obj = obj;
}

GameObject* Collision::GetGameObject()
{
    return obj;
}

CollisionType Collision::GetType()
{
    return this->type;
}

void Collision::SetType(CollisionType type)
{
    this->type = type;
}

/**/

CollisionRect::CollisionRect()
{

}

const RECT& CollisionRect::GetRect()
{
    // TODO: 여기에 return 문을 삽입합니다.
    return ctRect;
}

void CollisionRect::SetRect(const RECT& rt)
{
    this->ctRect = rt;
}

void CollisionRect::Render(HDC hdc)
{
    if (this->IsActive())
    {
        RenderRect(hdc, ctRect.left, ctRect.top, ctRect.right - ctRect.left, ctRect.bottom - ctRect.top);
    }
}

void CollisionRect::AddPos(float x, float y)
{
    ctRect.left += x;
    ctRect.right += x;
    ctRect.top += y;
    ctRect.bottom += y;
}

CollisionRect* CollisionManager::CreateCollisionRect(CollisionLayer layer, GameObject* obj, const RECT& rt)
{
    CollisionRect* coll = nullptr;
    if (nullptr != obj)
    {
        //   매번 생성이 아니라, 콜리젼 풀에서 가져오는 방식이라면? 
        coll = new CollisionRect();
        coll->SetGameObject(obj);
        coll->SetRect(rt);
        coll->SetType(CollisionType::RECT);
        coll->layer = layer;
        (*layerCollisionMap)[layer].insert(coll);
    }

    return coll;

}

void CollisionManager::DeleteCollision(Collision* coll)
{
    if (nullptr != coll)
    {
        unordered_set<Collision*>& setCollision = (*layerCollisionMap)[coll->layer];
        setCollision.erase(coll);

        // 콜리젼 풀 만들어서 해당 풀에 반환하는 식이면 더 좋을듯.
        delete coll;
    }
  
}

void CollisionManager::Init()
{

    brush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    this->checkCount = 0;

    layerCollisionMap = new unordered_map<CollisionLayer, unordered_set<Collision*>>();

    (*layerCollisionMap)[CollisionLayer::Player].reserve(10);
    (*layerCollisionMap)[CollisionLayer::PlayerAttack].reserve(200);
    (*layerCollisionMap)[CollisionLayer::Enemy].reserve(50);
    (*layerCollisionMap)[CollisionLayer::EnemyAttack].reserve(200);
    (*layerCollisionMap)[CollisionLayer::Item].reserve(10);

    layerMaskMap[CollisionLayer::Player] = uint8_t(CollisionLayer::Enemy) | uint8_t(CollisionLayer::EnemyAttack) | uint8_t(CollisionLayer::Item);
    layerMaskMap[CollisionLayer::PlayerAttack] = uint8_t(CollisionLayer::Enemy);
    layerMaskMap[CollisionLayer::Enemy] = uint8_t(CollisionLayer::Player) | uint8_t(CollisionLayer::PlayerAttack);
    layerMaskMap[CollisionLayer::EnemyAttack] = uint8_t(CollisionLayer::Player);
    layerMaskMap[CollisionLayer::Item] = uint8_t(CollisionLayer::Player);

}

void CollisionManager::Update()
{
    checkCount = 0;
    CollisionDetect();   
}

void CollisionManager::Render(HDC hdc)
{
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    for (const auto& pair : (*layerCollisionMap))
    {
        for (Collision* col : pair.second)
        {
            if (col->IsActive())
            {
                col->Render(hdc);
            }
        }
    }

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
}

void CollisionManager::Release()
{
    // layerMap
    // 남아있는 콜리젼 해제
    DeleteObject(brush);
    DeleteObject(pen);

    Singleton::ReleaseInstance();
}

void CollisionManager::CollisionDetect()
{
    uint8_t mask;
    for (const auto& pair : *layerCollisionMap)
    {
        mask = layerMaskMap[pair.first];

        for (const auto& pair2 : *layerCollisionMap)
        {
            // 검사 해야하는 레이어라면
            if (mask & uint8_t(pair2.first))    
            {
                CollisionDetect(pair.second, pair2.second);
            }
        }
    }
}

int CollisionManager::GetCheckCount()
{
    return this->checkCount;
}

int CollisionManager::GetCollisionCount()
{
    int collisionCount = 0;
    auto it = layerCollisionMap->begin();
    while (it != layerCollisionMap->end())
    {
        collisionCount += it->second.size();
        it++;
    }
    return collisionCount;
}

int CollisionManager::GetActivecollisionCount()
{
    // 성능 문제되면 호출 금지.
    int collisionCount = 0;
    for (const auto& pair : *layerCollisionMap)
    {
        for (const auto& col : pair.second)
        {
            if (col->IsActive())
            {
                collisionCount++;
            }
        }
    }
   
    return collisionCount;
}

void CollisionManager::CollisionDetect(const unordered_set<Collision*>& setColl1, const  unordered_set<Collision*>& setColl2)
{
    for (auto c1 : setColl1)
    {
        for (auto c2 : setColl2)
        {
            if (c1->IsActive() && c2->IsActive())
            {
                checkCount++;
                Detect(c1, c2);
            }
        }
    }
}

void CollisionManager::Detect(Collision* c1, Collision* c2)
{
    if (c1->GetType() == CollisionType::RECT && c2->GetType() == CollisionType::RECT)
    {
        CollisionRect* rt1 = static_cast<CollisionRect*>(c1);
        CollisionRect* rt2 = static_cast<CollisionRect*>(c2);

        if (RectInRect(rt1->GetRect(), rt2->GetRect()))
        {
            // 충돌.
            c1->detection(c2->obj);
            c2->detection(c1->obj);
        }
    }
}