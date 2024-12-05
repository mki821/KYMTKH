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
		m_isChange = true;
		float angle = rand() % 180 + 180;
		float rad = angle * Deg2Rad;
		this->SetDir({ cos(rad), -sin(rad) });
	}
}
