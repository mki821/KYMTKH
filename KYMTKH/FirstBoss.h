#pragma once
#include "Boss.h"


class RandomMoveProj;
class Texture;
class FirstBoss :
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
	FirstBoss();
	~FirstBoss();
public:
	void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
public:
	void ChangePattern();
	Vector2 GetRandomPos();
	Vector2 GetBossRoundPos(int range);
private:
	void FirstPattern();
	void FirstPatternUpdate();
	void SecondPattern();
	void SecondPatternUpdate();
	void ThirdPatternUpdate();
	void FourthPatternUpdate();
	void FourthPattern();
	void FifthPatternUpdate();
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
	void CircleRandomShot(int count, Vector2 pos);
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
	bool m_firstPattern = true;
	bool m_stop = false;
	float m_waitTime = 0;
private:
	Texture* m_blueTexture = nullptr;
};


