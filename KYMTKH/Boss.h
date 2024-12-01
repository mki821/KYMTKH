#pragma once

#include "Object.h"

class Player;

class Boss : public Object {
public:
	Boss();
	virtual ~Boss();
public:
	virtual void Init() override { }
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
public:
	virtual void EnterCollision(Collider* other) override;
public:
	void SetPlayer(Player* player) { m_player = player; }
protected:
	Player* m_player;
	int m_hp;
	float m_patternTimer = 0.0f;
	std::function<void()> m_patternFunc;
};
