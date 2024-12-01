#pragma once

#include "Object.h"

class Texture;

class Player : public Object {
public:
	Player();
	~Player();
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
public:
	virtual void EnterCollision(Collider* other) override;
private:
	void ClampPos();
	void CreateProjectile();
private:
	Texture* m_pTex;
public:
	void SetHp(int hp) { m_hp = hp; }
	const int& GetHp() const { return m_hp; }
	void SetSpeed(float speed) { m_speed = speed; }
	const float& GetSpeed() const { return m_speed; }
private:
	int m_hp;
	float m_speed;
	float m_timer = 0.0f;
};

