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
protected:
	void Move(Vector2 targetPos, float time = 1.0f);
protected:
	int m_hp;
	float m_patternTimer = 0.0f;
	std::function<void()> m_patternFunc;
private:
	Vector2 m_moveStartPos = { 0.0f, 0.0f };
	Vector2 m_targetPos = { 0.0f, 0.0f };
	float m_moveTime = 0.0f;
	float m_moveTimer = 0.0f;
	bool m_isMove = false;
};
