#pragma once
#include "Boss.h"

enum class Pattern {
	First, 
	Second, 
	Third,
	Fourth,
	Dead
};

class RandomMoveProj;
class FirstBoss :
    public Boss
{
public:
	FirstBoss();
	~FirstBoss();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
public:
	void ChangePattern();
private:
	void FirstPattern();
	void FirstPatternUpdate();
	void SecondPattern();
	void SecondPatternUpdate();
	void ThirdPatternUpdate();
	void FourthPatternUpdate();
	void FourthPattern();
private:
	void One();
	void Two();
	void Three();
	void Four();
	void Five();
	void Six();
private:
	void StopAndRandomMoveShot(float time,float speed);
	void StopAndChaseShot(int shotDeg);
	void CircleShot(int shotDeg, float speed);
	void SpreadShot(int count, Vector2 dir, float speed);
	void RandomMoveShot(int count);
	void FiveShot();
public:
	const Object* GetPlayer() const { return m_player; }
private:
	const Object* m_player;
	int m_angleModifier = 0;
	Vector2 m_originPos = {};
private:
	float m_timer = 0.0f;
	float m_timer2 = 0.0f;
private:
	Pattern m_curPattern = Pattern::First;
	int m_changePatternCount = 0;
	bool m_firstPattern = true;;
	bool m_stop = false;
};

