#pragma once

class TimeManager {
	DECLARE_SINGLE(TimeManager)
public:
	void Init();
	void Update();
public:
	const float& GetDT() const { return m_dT; }
private:
	LARGE_INTEGER m_llPrevCnt = {};
	LARGE_INTEGER m_llCurCnt = {};
	LARGE_INTEGER m_llFrequency = {};
	float m_dT = 0.0f;

	UINT m_fps = 0;
	UINT m_frameCnt = 0;
	float m_frameTime = 0.0f;
};
