#pragma once

#include "Object.h"

class Projectile : public Object {
public:
	Projectile();
	virtual ~Projectile();
public:
	void Update() override;
	void Render(HDC hdc) override;
public:
	void SetSpeed(float speed) { m_speed = speed; }
	const float& GetSpeed() const { return m_speed; }
	void SetDir(Vector2 dir) { dir.Normalize(); m_vDir = dir; }
	void SetDir(float angle) {
		float delta = angle * Deg2Rad;
		m_vDir = { cosf(delta), -sinf(delta) };
	}
	const Vector2& GetDir() const { return m_vDir; }
protected:
	float m_speed;
	Vector2 m_vDir;
};

