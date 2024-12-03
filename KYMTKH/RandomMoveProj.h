#pragma once
#include "Projectile.h"
class RandomMoveProj :
    public Projectile
{
public:
    RandomMoveProj();
    ~RandomMoveProj();
public:
    void Init() override;
    void Update() override;
public:
    void SetChangeSpeed(float speed) { m_changeSpeed = speed; }
private:
    Vector2 RandomDir();
public:
    void Stop();
    void Remove();
    void Delete();
private:
    float m_changeSpeed = 0;
};

