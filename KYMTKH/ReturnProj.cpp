#include "pch.h"
#include "ReturnProj.h"
#include "TimeManager.h"
#include "EventManager.h"


ReturnProj::ReturnProj()
	: m_rotationSpeed(2.0f),
	m_isReturning(false), m_isExiting(false), m_currentAngle(0.0f), m_radius(100.0f) { }

ReturnProj::~ReturnProj() { }

void ReturnProj::Init() {
	Projectile::Init();
	m_radius = (m_target - m_vPos).Length();
	m_currentAngle = atan2(m_vPos.y - m_target.y, m_vPos.x - m_target.x);
}

void ReturnProj::Update() {
	if (!m_isReturning) {
		m_vPos += m_vDir * m_speed * fDT;
		m_changeTime -= fDT;

		if (m_changeTime <= 0.0f) {
			m_isReturning = true;
			m_radius = (m_target - m_vPos).Length();
			m_currentAngle = atan2(m_vPos.y - m_target.y, m_vPos.x - m_target.x);
			m_speed = m_changeSpeed;
		}
	}
	else if (!m_isExiting) {

		// 원 궤도에서 회전
		m_currentAngle += m_rotationSpeed * fDT; // 각도 증가
		m_vPos.x = m_target.x + cos(m_currentAngle) * m_radius;
		m_vPos.y = m_target.y + sin(m_currentAngle) * m_radius;
		if (m_radius >= 50) {
			m_radius -= fDT * 200;
		}
		else {
			m_exitTime -= fDT;
			if (m_exitTime <= 0.0f) {
				m_isExiting = true;
			}
			//m_isExiting = true;
		}
	}
	else {
		m_vDir = { sin(m_currentAngle), -cos(m_currentAngle) };
		m_vPos += m_vDir * m_speed * fDT;
	}

	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}
