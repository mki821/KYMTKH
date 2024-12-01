#pragma once

#include "Boss.h"

class JHBoss : public Boss {
public:
	JHBoss();
	~JHBoss();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	void One();
	void Two();
	void Three();
public:
	const bool GetScalceUp() const { return m_scaleUp; }
private:
	float m_timer = 0.0f;
	int m_angleModifier = 0;
	bool m_scaleUp = false;
};
