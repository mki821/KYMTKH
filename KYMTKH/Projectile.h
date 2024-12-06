#pragma once

#include "Object.h"

class Texture;

class Projectile : public Object {
public:
	Projectile();
	virtual ~Projectile();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
public:
	virtual void EnterCollision(Collider* other) override;
public:
	void SetSpeed(float speed) { m_speed = speed; }
	const float& GetSpeed() const { return m_speed; }
	void SetLifeTime(float lifeTime) { m_lifeTime = lifeTime; }
	void SetDir(Vector2 dir) { dir.Normalize(); m_vDir = dir; }
	void SetDir(float angle) {
		float delta = angle * Deg2Rad;
		m_vDir = { cosf(delta), -sinf(delta) };
	}
	const Vector2& GetDir() const { return m_vDir; }
protected:
	float m_speed;
	float m_lifeTime = 2.0f;
	Vector2 m_vDir;
public:
	void SetTexture(Texture* texture);
protected:
	HDC m_rotateDC = NULL;
	HBITMAP m_rotateBitmap = NULL;
	RECT m_rt = { };
	HBRUSH m_hBrush = NULL;
	Texture* m_pTex = nullptr;
};

