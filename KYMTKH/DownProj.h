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
    float m_baseAngle = 270;
    float m_angleRange = 60;
    float m_changeAngle = 0;
    float m_angle = 0;
    float m_timer = 0;
};

