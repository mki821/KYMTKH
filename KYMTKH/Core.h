#pragma once

class Core {
	DECLARE_SINGLE(Core)
public:
	bool Init(HWND _hWnd);
	void GameLoop();
	void CleanUp();
private:
	void MainUpdate();
	void MainRender();
	void CreateGDI();
public:
	const HWND& GetHWnd() const { return m_hWnd; }
	const HDC& GetMainDC() const { return m_hDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType) { return m_colorBrushs[(UINT)_eType]; }
	const HPEN& GetPen(PEN_TYPE _eType) { return m_colorPens[(UINT)_eType]; }
private:
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};
private:
	HWND m_hWnd;
	HDC m_hDC;
	HDC m_hBackDC;
	HBITMAP m_hBackBit;
};
