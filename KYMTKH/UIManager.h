#pragma once

#include "UI.h"

class UIManager {
	DECLARE_SINGLE(UIManager)
public:
	void Update();
	void Render(HDC hdc);
	void Clear();
public:
	void AddUI(const wstring& name, UI* ui) {
		ui->Init();
		m_mapUI[name] = ui;
	}
	void RemoveUI(const wstring& name) {
		delete m_mapUI.at(name);
		m_mapUI.erase(name);
	}
	const UI* GetUI(const wstring& name) const { return m_mapUI.at(name); }
private:
	std::map<wstring, UI*> m_mapUI;
};
