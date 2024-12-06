#include "pch.h"
#include "DownProj.h"
#include "TimeManager.h"

DownProj::DownProj()
{
}

DownProj::~DownProj()
{
}

void DownProj::Update()
{
	m_vPos += m_vDir * fDT * m_speed;
	m_changeTime -= fDT;
	if (m_changeTime <= 0 && !m_isChange) {
		float multiple = rand() % 2 == 0 ? -1 : 1;
		m_isChange = true;
		m_changeAngle = (rand() % int(m_angleRange - m_angleRange / 2)* multiple);
	}
	if (m_changeAngle != 0) {
		if (m_timer <= 1) {
			m_timer += fDT;
			m_angle = std::lerp(
				atan2(m_vDir.y, m_vDir.x) * Rad2Deg,
				m_baseAngle + m_changeAngle,
				m_timer
			);

			this->SetDir(m_angle);
		}
	}
}
