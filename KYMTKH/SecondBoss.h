#pragma once
#include "Boss.h"


class SecondBoss :
    public Boss
{
	enum class Pattern {
		First,
		Second,
		Third,
		Fourth,
		Fifth,
		Dead
	};
public:
	SecondBoss();
	~SecondBoss();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
public:
	void ChangePattern();
	Vector2 GetRandomPos();
private:
	void FirstPatternUpdate();
	void SecondPatternUpdate();
	void ThirdPatternUpdate();
	void FourthPatternUpdate();
private:
	void One();
	void Two();
private:
	void CircleRotateShot(int baseAngle);
	void FiveCircleRotateShot(int baseAngle);
	void CircleRandomShot(int count);
	void DownShot(int count);
	void CircleReturnShot(int count);
	void RandomMoveShot(int count);
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
	bool m_stop = false;
private:
	int m_firstPattenAngle = 0;
	bool m_turn = true;
	bool m_firstPattern = true;;
};

