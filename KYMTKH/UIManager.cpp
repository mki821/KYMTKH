#include "pch.h"
#include "GDISelector.h"
#include "UI.h"
#include "EventManager.h"
#include "UIManager.h"

void UIManager::Update() {
	for (auto ui : m_mapUI) {
		if(!ui.second->GetIsDead())
			ui.second->Update();
	}
}

void UIManager::Render(HDC hdc) {
	GDISelector a(hdc, BRUSH_TYPE::BLACK);
	PatBlt(hdc, 0, 0, GAME_LEFT, SCREEN_HEIGHT, BLACKNESS);
	PatBlt(hdc, GAME_RIGHT, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACKNESS);

	for (auto ui : m_mapUI) {
		if (!ui.second->GetIsDead())
			ui.second->Render(hdc);
	}
}

void UIManager::Clear() {
	for (auto ui : m_mapUI) {
		GET_SINGLE(EventManager)->DeleteObject(ui.second);
	}
	m_mapUI.clear();
}
