#pragma once

#include "Component.h"

class Collider : public Component {
public:
    Collider();
    ~Collider();
public:
    virtual void LateUpdate() override;
    virtual void Render(HDC hdc) override;
public:
    void EnterCollision(Collider* other); // �浹����
    void StayCollision(Collider* other); // �浹��
    void ExitCollision(Collider* other); // �浹����
    const UINT& GetID() const { return m_ID; }
private:
    UINT m_ID; // �浹ü ���� ID��
    static UINT m_sNextID;
public:
    void SetSize(Vector2 vSize) { m_vSize = vSize; }
    const Vector2& GetSize() const { return m_vSize; }
    void SetOffSetPos(Vector2 vOffsetPos) { m_vOffset = vOffsetPos; }
    const Vector2& GetOffSetPos() const { return m_vOffset; }
    const Vector2& GetLatedUpatedPos() const { return m_vLateUpdatedPos; }
private:
    Vector2 m_vSize;
    Vector2 m_vOffset;
    Vector2 m_vLateUpdatedPos;
    bool m_showDebug = false;
};
