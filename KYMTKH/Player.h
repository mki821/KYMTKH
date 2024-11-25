#pragma once

#include "Object.h"

class Texture;

class Player : public Object {
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC hdc) override;
private:
	void CreateProjectile();
private:
	Texture* m_pTex;
public:
	void SetSpeed(float speed) { m_speed = speed; }
	const float& GetSpeed() const { return m_speed; }
private:
	float m_speed;
};

