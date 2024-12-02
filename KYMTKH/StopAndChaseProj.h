#pragma once
#include "Projectile.h"
class FirstBoss;
class StopAndChaseProj :
    public Projectile
{
public:
    StopAndChaseProj();
    ~StopAndChaseProj();
public:
    void Init() override;
    void Update() override;
public:
    void SetOwner(FirstBoss* owner) { m_owner = owner; }
    void SetDirChangeTime(float time) { m_dirChangeTime = time; }
    void SetChangeSpeed(float speed) { m_changeSpeed = speed; }
private:
    float m_dirChangeTime = 0;
    float m_changeSpeed = 0;

    FirstBoss* m_owner = nullptr;
    const Object* m_player;
    bool chasePlayer = false;
    float m_timer = 0;
};

