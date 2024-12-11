#pragma once

#include "UI.h"
#include "EventManager.h"

class Texture;

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
		GET_SINGLE(EventManager)->DeleteObject(m_mapUI.at(name));
		m_mapUI.erase(name);
	}
	UI* GetUI(const wstring& name) const { return m_mapUI.find(name) != m_mapUI.end() ? m_mapUI.at(name) : nullptr; }
public:
	std::map<wstring, UI*> m_mapUI;
	Texture* m_input = nullptr;
};
