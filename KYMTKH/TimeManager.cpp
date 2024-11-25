#include "pch.h"
#include "Core.h"
#include "InputManager.h"
#include "TimeManager.h"

void TimeManager::Init() {
	QueryPerformanceCounter(&m_llPrevCnt);
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update() {
	QueryPerformanceCounter(&m_llCurCnt);

	m_dT = (float)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart) / m_llFrequency.QuadPart;
	m_llPrevCnt = m_llCurCnt;

	++m_frameCnt;
	m_frameTime += m_dT;
	if (m_frameTime >= 1.0f) {
		m_fps = (UINT)(m_frameCnt / m_frameTime);
		m_frameCnt = 0;
		m_frameTime = 0.0f;

		//wstring strfps = std::to_wstring(m_fps);
		//wstring strdt = std::to_wstring(m_dT);
		//wstring str = L"FPS: " + strfps + L" DT: " + strdt;
		//TextOut(GET_SINGLE(Core)->GetMainDC(), 0, 0, str.c_str(), str.length());

		static wchar_t buf[100] = {};
		swprintf_s(buf, L"FPS: %d DT: %f", m_fps, m_dT);
		SetWindowText(GET_SINGLE(Core)->GetHWnd(), buf);
	}
}
