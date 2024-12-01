#pragma once
#include "Scene.h"
class Y_TestScene :
    public Scene
{
public:
    const Object* GetPlayer() const { return m_player; }
    void SetPlayer(Object* player) { m_player = player; }
private:
    void Init() override;
private:
    Object* m_player = nullptr;
};

