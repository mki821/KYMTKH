#include "pch.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Image.h"
#include "SelectScene.h"

SelectScene::SelectScene() {
	m_vecSceneNames = { L"Y_TestScene", L"TestScene" };
}

void SelectScene::Init() {
	for (int i = 0; i < m_vecSceneNames.size(); ++i) {
		Image* img = new Image;

		m_vecSceneImages.push_back(img);
	}
}

void SelectScene::Update() {
	if (m_isChangingIndex) {
		m_timer += fDT;
		m_currentSceneIndex = std::lerp(m_prevSceneIndex, m_targetSceneIndex, m_timer * 5.0f);

		if (m_timer >= 0.2f) {
			m_timer = 0.0f;
			m_currentSceneIndex = m_targetSceneIndex;
			m_isChangingIndex = false;
		}
	}
	else {
		if (GET_KEY_DOWN(KEY_TYPE::LEFT)) {
			m_prevSceneIndex = m_currentSceneIndex;
			m_targetSceneIndex = max(m_currentSceneIndex - 1, 0);
			m_isChangingIndex = true;
		}
		if (GET_KEY_DOWN(KEY_TYPE::RIGHT)) {
			m_prevSceneIndex = m_currentSceneIndex;
			m_targetSceneIndex = min(m_currentSceneIndex + 1, m_vecSceneNames.size() - 1);
			m_isChangingIndex = true;
		}

		if (GET_KEY_DOWN(KEY_TYPE::SPACE)) {
			GET_SINGLE(SceneManager)->LoadScene(m_vecSceneNames[m_currentSceneIndex]);
		}
	}

	for (int i = 0; i < m_vecSceneImages.size(); ++i) {
		float diff = i - m_currentSceneIndex;
		m_vecSceneImages[i]->SetPos({ GAME_CENTER + 400.0f * diff, SCREEN_HEIGHT / 2.0f });
		m_vecSceneImages[i]->SetSize({ 140.0f * (3 - abs(diff)), 250.0f * (3 - abs(diff)) });
	}
}

void SelectScene::Render(HDC hdc) {
	for (int i = 0; i < m_vecSceneImages.size(); ++i) {
		m_vecSceneImages[i]->Render(hdc);
	}
}

void SelectScene::Release() {
	m_vecSceneImages.clear();
}
