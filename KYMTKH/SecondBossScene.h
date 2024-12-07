#pragma once
#include "Scene.h"
class SecondBossScene :
    public Scene
{
public:
    const Object* GetPlayer() const { return m_player; }
    void SetPlayer(Object* player) { m_player = player; }
private:
    void Init() override;
    void Release() override;
private:
    Object* m_player = nullptr;
};

