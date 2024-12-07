#include "pch.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "LemniscateParent.h"
#include "CircleCollider.h"
#include "Lemniscate.h"

Lemniscate::Lemniscate(float startAngle) : Projectile(), m_currentAngle(startAngle), m_rotationAngle(startAngle / 4) { }
Lemniscate::~Lemniscate() { }

void Lemniscate::Init() {
	GetComponent<CircleCollider>()->SetSize(m_vSize);

	m_createdPos = m_vPos;
}

void Lemniscate::Update() {
	m_currentAngle += fDT * m_speed;
	if (m_currentAngle >= 360.0f) m_currentAngle -= 360.0f;
	else if (m_currentAngle < 0.0f) m_currentAngle += 360.0f;

	m_rotationAngle += fDT * m_rotationSpeed;;
	if (m_rotationAngle >= 360.0f) m_rotationAngle -= 360.0f;
	else if (m_rotationAngle < 0.0f) m_rotationAngle += 360.0f;

	SizeUp();

	float delta = m_currentAngle * Deg2Rad;
	float scale = 2.0f / (3.0f - cosf(delta * 2.0f)) * m_currentScale;
	float x = cosf(delta) * scale;
	float y = sinf(delta * 2.0f) * 0.5f * scale;

	float delta2 = m_rotationAngle * Deg2Rad;
	float xp = x * cosf(delta2) - y * sinf(delta2);
	float yp = x * sinf(delta2) + y * cosf(delta2);

	Vector2 ownerPos = m_owner->GetPos();
	
	m_vPos = ownerPos + Vector2{ xp, yp } * 100.0f;

	Vector2 offset = m_vPos - ownerPos;
	float delta3 = m_turnSpeed * Deg2Rad;
	float tempX = offset.x * cosf(delta3) - offset.y * sinf(delta3);
	float tempY = offset.x * sinf(delta3) + offset.y * cosf(delta3);
	m_vPos = ownerPos + Vector2{ tempX * (m_turnSpeed < 0 ? -1 : 1), tempY};

	SetDir(m_vPos - m_prevPos);
	m_prevPos = m_vPos;
}

void Lemniscate::SizeUp() {
	if (m_sizeUpTimer >= 2.0f) return;

	m_sizeUpTimer += fDT;
	if (m_sizeUpTimer > 2.0f) m_sizeUpTimer = 2.0f;

	m_currentScale = std::lerp(0.0f, 3.5f, m_sizeUpTimer / 2.0f);
}
