#pragma once
#include "Projectile.h"
class DownProj :
    public Projectile
{
public:
    DownProj();
    ~DownProj();
private:
    void Update() override;
public:
    void SetChangeTime(float time) { m_changeTime = time; }
private:
    float m_changeTime = 0;
    bool m_isChange = false;
};

