#include "MissilePattern.h"
#include "TimerManager.h"


MissilePattern::MissilePattern()
{
    startPos = { 0.0f, 0.0f };
    fireCount = 0;
    fireDelay = 0.1f;
    type = nullptr;
    angleMin = 90.0f;
    angleMax = 90.0f;
    accumulatedTime = 0.0f;
}

void MissilePattern::Init(EImageKey key, FPOINT startPos, int fireCount, float fireDelay, float speed, float angleMin, float angleMax)
{
    accumulatedTime = TimerManager::GetInstance()->GetAccumulatedTime();

    this->key = key;
    this->startPos = startPos;
    this->fireCount = fireCount;
    this->fireDelay = fireDelay;
    this->speed = speed;
    this->angleMin = angleMin;
    this->angleMax = angleMax;
}

FPOINT MissilePattern::getStartPoint()
{
    return startPos;
}

std::vector<SpawnMissileInfo> MissilePattern::getMissilesInfo()
{
    std::vector<SpawnMissileInfo> missilesInfo;

    if (angleMin == angleMax)
    {
        for (int i = 0; i < fireCount; i++)
        {
            SpawnMissileInfo info{ key, startPos, accumulatedTime + (fireDelay * i), speed, angleMin };
            missilesInfo.push_back(info);
        }
    }
    else
    {
        float theta = (angleMax - angleMin) / float(fireCount);
        for (int i = 0; i < fireCount; i++)
        {
            float angle = angleMin + theta * i;
            SpawnMissileInfo info{ key, startPos, accumulatedTime + fireDelay, speed, angle };
            missilesInfo.push_back(info);
        }
    }

    return missilesInfo;
}
