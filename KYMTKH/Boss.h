#pragma once

#include "Object.h"

class Boss : public Object {
public:
	Boss();
	virtual ~Boss();
public:
	void Update() override;
	void Render(HDC hdc) override;
public:
	virtual void EnterCollision(Collider* other) override;
private:
	int m_hp;
};
