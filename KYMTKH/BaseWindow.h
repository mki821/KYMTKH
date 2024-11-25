#pragma once

class BaseWindow {
public:
	BaseWindow();
	~BaseWindow();
public:
	int Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _CmdShow);
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	ATOM MyRegisterClass();
	void createWindow();
	void showWindow(int _CmdShow);
	void updateWindow();
	int  MessageLoop();
private:
	HINSTANCE m_hInst;
	HWND	  m_hWnd;
};
