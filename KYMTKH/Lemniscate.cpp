#include "pch.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "JHBoss.h"
#include "Lemniscate.h"

Lemniscate::Lemniscate() : Projectile() { }
Lemniscate::~Lemniscate() { }

void Lemniscate::Init() {
	m_createdPos = m_vPos;
}

void Lemniscate::Update() {
	m_currentAngle += fDT * 300.0f;
	if (m_currentAngle >= 360.0f) m_currentAngle -= 360.0f;

	m_rotationAngle += fDT * 50.0f;
	if (m_rotationAngle >= 360.0f) m_rotationAngle -= 360.0f;

	SizeUp();

	float delta = m_currentAngle * Deg2Rad;
	float scale = 2.0f / (3.0f - cosf(delta * 2.0f)) * m_currentScale;
	float x = cosf(delta) * scale;
	float y = sinf(delta * 2.0f) * 0.5f * scale;

	float delta2 = m_rotationAngle * Deg2Rad;
	float xp = x * cosf(delta2) - y * sinf(delta2);
	float yp = x * sinf(delta2) + y * cosf(delta2);	
	
	m_vPos = m_createdPos + Vector2{ xp, yp } * 100.0f;

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Lemniscate::SizeUp() {
	if (!m_owner->GetScalceUp()) return;
	if (m_sizeUpTimer >= 1.0f) return;

	m_sizeUpTimer += fDT;
	if (m_sizeUpTimer > 1.0f) m_sizeUpTimer = 1.0f;

	m_currentScale = std::lerp(1.0f, 5.0f, m_sizeUpTimer);
}
