#include "GameObject.h"

void GameObject::Init()
{
}

void GameObject::Release()
{

}

void GameObject::Update()
{
}

void GameObject::Render(HDC hdc)
{
}

void GameObject::SetActive(bool _bActive)
{
    this->bActive = _bActive;
}

bool GameObject::IsActive()
{
    return this->bActive;
}

GameObject::GameObject()
    :bActive(true)
{
}

GameObject::~GameObject()
{
}

void GameObject::AddTag(const wstring& tag)
{
    this->tags.insert(tag);
}

void GameObject::AddTags(const unordered_set<wstring> tags)
{
    for (const auto& tag : tags)
    {
        AddTag(tag);
    }
}

const unordered_set<wstring>& GameObject::GetTags()
{
    return this->tags;
}
