#pragma once
#include "Projectile.h"

class ReturnProj : public Projectile {
public:
    ReturnProj();
    virtual ~ReturnProj();

    virtual void Init() override;
    virtual void Update() override;

    void SetChangeTime(float changeTime) { m_changeTime = changeTime; }
    void SetRotationSpeed(float rotationSpeed) { m_rotationSpeed = rotationSpeed; }
    void SetTarget(Vector2 target) { m_target = target; }
    void SetChangeSpeed(float speed) { m_changeSpeed = speed; }
    void SetExitTime(float time) { m_exitTime = time; }

private:
    float m_changeTime;       // 직선 이동 후 궤도 전환 시간
    float m_rotationSpeed;    // 원형 회전 속도
    float m_exitTime;         // 원 궤적을 돌고 나가는 시간
    float m_currentAngle;     // 현재 각도
    float m_radius;           // 원 반지름
    bool m_isReturning;       // 원으로 진입했는지 여부
    Vector2 m_target;         // 원 중심 좌표
    bool m_isExiting;
    float m_changeSpeed;
};
