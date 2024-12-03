#pragma once
#include "Projectile.h"
class StopAndRandomMoveProj :
    public Projectile
{
public: 
    StopAndRandomMoveProj();
    ~StopAndRandomMoveProj();
public:
    void Init() override;
    void Update() override;
public:
    void SetDirChangeTime(float time) { m_dirChangeTime = time; }
    void SetChangeSpeed(float speed) { m_changeSpeed = speed; }
private:
    bool m_changeMove = false;
    float m_timer = 0;

    float m_dirChangeTime = 0;
    float m_changeSpeed = 0;
};

