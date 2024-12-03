#pragma once
#include "Boss.h"

class RandomMoveProj;
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
	void Two();
	void Three();
	void Four();
private:
private:
	void StopAndRandomMoveShot(float time,float speed);
	void StopAndChaseShot(int shotDeg);
	void CircleShot(int shotDeg, float speed);
	void SpreadShot(int count, Vector2 dir);
	void RandomMoveShot(int count);
	void FiveShot();
public:
	const bool GetScalceUp() const { return m_scaleUp; }
	const Object* GetPlayer() const { return m_player; }
private:
	float m_timer = 0.0f;
	int m_angleModifier = 0;
	bool m_scaleUp = false;
	const Object* m_player;
private:
	vector<RandomMoveProj*> m_projVec;
public:
	void ClearVector();
};

