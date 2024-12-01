#pragma once

#include "Projectile.h"

class JHBoss;

class Lemniscate : public Projectile {
public:
	Lemniscate(float startAngle);
	~Lemniscate();
public:
	virtual void Init() override;
	virtual void Update() override;
private:
	void SizeUp();
public:
	void SetOwner(JHBoss* owner) { m_owner = owner; }
private:
	JHBoss* m_owner = nullptr;
public:
	void SetRotationSpeed(float speed) { m_rotationSpeed = speed; }
	void SetTurnSpeed(float speed) { m_turnSpeed = speed; }
private:
	float m_sizeUpTimer = 0.0f;
	float m_currentAngle = 0.0f;
	float m_rotationAngle = 0.0f;
	float m_rotationSpeed = 2.0f;
	float m_turnSpeed = 100.0f;
	float m_currentScale = 1.0f;
	Vector2 m_createdPos;
};
