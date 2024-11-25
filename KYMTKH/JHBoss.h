#pragma once

#include "Boss.h"

class JHBoss : public Boss {
public:
	JHBoss();
	~JHBoss();
public:
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	float m_timer = 0.0f;
	int m_angleModifier = 0;
};
