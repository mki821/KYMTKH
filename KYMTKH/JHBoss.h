#pragma once

#include "Boss.h"

class Lemniscate;

class JHBoss : public Boss {
public:
	JHBoss();
	~JHBoss();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	void FirstPattern();
	void SecondPattern();
private:
	void One();
	void Two();
	void Three();
private:
	float m_timer = 0.0f;
	float m_timer3 = 0.0f;
	int m_angleModifier = 0;
};
