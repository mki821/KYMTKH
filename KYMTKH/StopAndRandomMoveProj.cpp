#include "pch.h"
#include "StopAndRandomMoveProj.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "CircleCollider.h"
#include "Collider.h"

StopAndRandomMoveProj::StopAndRandomMoveProj()
{
}

StopAndRandomMoveProj::~StopAndRandomMoveProj()
{
}

void StopAndRandomMoveProj::Init()
{
	GetComponent<CircleCollider>()->SetSize(GetSize());
}

void StopAndRandomMoveProj::Update()
{
	if (!m_changeMove) {
		m_timer += fDT;
		float gap = m_dirChangeTime - m_timer;
		if (m_timer > m_dirChangeTime) {
			m_changeMove = true;
			float angle = rand() % 180 + 180;
			float rad = angle * Deg2Rad;
			this->SetSpeed(m_changeSpeed);
			this->SetDir({ cos(rad), -sin(rad) });
		}
		else if (gap > 0.2f && gap < 0.3f) {
			this->SetSpeed(this->m_speed / 2);
		}
		else if (gap > 0.f && gap < 0.1f) {
			this->SetSpeed(0);
		}
	}

	m_vPos += m_vDir * m_speed * fDT;
	m_lifeTime -= fDT;
	if (m_lifeTime <= 0.0f) {
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}
