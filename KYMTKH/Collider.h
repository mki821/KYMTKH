#pragma once

#include "Component.h"

class Collider : public Component {
public:
    Collider();
    ~Collider();
public:
    virtual void LateUpdate();
    virtual void Render(HDC hdc);
public:
    virtual void EnterCollision(Collider* other); // 충돌진입
    virtual void StayCollision(Collider* other); // 충돌중
    virtual void ExitCollision(Collider* other); // 충돌해제
    const UINT& GetID() const { return m_ID; }
protected:
    UINT m_ID = 0; // 충돌체 고유 ID값
    static UINT m_sNextID;
public:
    const bool& GetEnable() const { return m_enabled; }
    void SetEnable(bool enabled) { m_enabled = enabled; }
    void SetSize(Vector2 vSize) { m_vSize = vSize; }
    const Vector2& GetSize() const { return m_vSize; }
    void SetOffSetPos(Vector2 vOffsetPos) { m_vOffset = vOffsetPos; }
    const Vector2& GetOffSetPos() const { return m_vOffset; }
    const Vector2& GetLatedUpatedPos() const { return m_vLateUpdatedPos; }
protected:
    bool m_enabled = true;
    Vector2 m_vSize;
    Vector2 m_vOffset;
    Vector2 m_vLateUpdatedPos;
    bool m_showDebug = false;
};
