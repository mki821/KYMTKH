#include "pch.h"
#include "GDISelector.h"
#include "UIManager.h"

void UIManager::Update() {
	for (auto ui : m_mapUI) {
		ui.second->Update();
	}
}

void UIManager::Render(HDC hdc) {
	GDISelector a(hdc, BRUSH_TYPE::BLACK);
	Rectangle(hdc, 0, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT);
	Rectangle(hdc, SCREEN_WIDTH / 3 * 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	for (auto ui : m_mapUI) {
		ui.second->Render(hdc);
	}
}

void UIManager::Clear() {
	for (auto ui : m_mapUI) {
		delete ui.second;
	}
	m_mapUI.clear();
}
