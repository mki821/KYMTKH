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
    float m_changeTime;       // ���� �̵� �� �˵� ��ȯ �ð�
    float m_rotationSpeed;    // ���� ȸ�� �ӵ�
    float m_exitTime;         // �� ������ ���� ������ �ð�
    float m_currentAngle;     // ���� ����
    float m_radius;           // �� ������
    bool m_isReturning;       // ������ �����ߴ��� ����
    Vector2 m_target;         // �� �߽� ��ǥ
    bool m_isExiting;
    float m_changeSpeed;
};
