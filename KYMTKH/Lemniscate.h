#pragma once

#include "Projectile.h"

class JHBoss;

class Lemniscate : public Projectile {
public:
	Lemniscate();
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
private:
	float m_sizeUpTimer = 0.0f;
	float m_currentAngle = 0.0f;
	float m_rotationAngle = 0.0f;
	float m_currentScale = 1.0f;
	Vector2 m_createdPos;
};
