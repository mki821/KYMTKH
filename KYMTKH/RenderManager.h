#pragma once

class RenderManager {
	DECLARE_SINGLE(RenderManager)
public:
	~RenderManager();
public:
	void Init();
	void BeforeRender();
	void Render(HDC hdc);
public:
	const HDC& GetDC() const { return m_hDC; }
private:
	HDC m_hDC = NULL;
	HBITMAP m_hBitmap = NULL;
	HBRUSH m_hBrush = NULL;
	int width;
};

