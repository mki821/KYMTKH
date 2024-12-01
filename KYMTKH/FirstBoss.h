#pragma once
#include "Boss.h"
class FirstBoss :
    public Boss
{
public:
	FirstBoss();
	~FirstBoss();
public:
	void Init() override { }
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
private:
	void One();
	void CircleShot(int shotDeg);
	void SpreadShot(int count);
public:
	const bool GetScalceUp() const { return m_scaleUp; }
private:
	float m_timer = 0.0f;
	int m_angleModifier = 0;
	bool m_scaleUp = false;

	const Object* m_player;

	int bulletCount = 4;
	bool isStop = false;
};

