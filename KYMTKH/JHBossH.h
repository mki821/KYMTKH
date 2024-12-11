#pragma once

#include "Boss.h"

class Texture;
class Lemniscate;

class JHBossH : public Boss {
	enum class Pattern {
		First, Second, Third
	};
public:
	JHBossH();
	~JHBossH();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	void FirstPatternUpdate();
	void SecondPattern();
	void ThirdPattern();
	void ThirdPatternUpdate();
private:
	void One();
	void Two();
	void Three();
	void Four();
private:
	Pattern m_eCurPattern = Pattern::First;
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
	float m_timer3 = 0.0f;
	int m_angleModifier = 0;
	int m_turnDirection = -1;
private:
	std::random_device rd;
private:
	Texture* m_pProjectile15 = nullptr;
	Texture* m_pProjectile10 = nullptr;
};
