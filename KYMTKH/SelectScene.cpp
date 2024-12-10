#include "pch.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "Image.h"
#include "Background.h"
#include "UIManager.h"
#include "SelectScene.h"

SelectScene::SelectScene() {
	m_vecSceneNames = { L"Y_TestScene", L"TestScene", L"SecondBossScene" };
}

void SelectScene::Init() {
	LOAD_RES(L"Heart", L"Texture\\UI\\Heart.bmp");
	LOAD_RES(L"BossHealthBar", L"Texture\\UI\\BossHealthBar.bmp");
	LOAD_RES(L"ExitBtn", L"Texture\\UI\\ExitBtn.bmp");
	LOAD_RES(L"Y_TestScene", L"Texture\\Background\\FirstBossBackGround.bmp");
	LOAD_RES(L"TestScene", L"Texture\\Background\\JHBackground.bmp");
	LOAD_RES(L"SecondBossScene", L"Texture\\Background\\SecondBossBackGround.bmp");
	LOAD_RES(L"Projectile_15x15", L"Texture\\Projectile\\Projectile_15x15.bmp");
	LOAD_RES(L"SelectBackground", L"Texture\\Background\\SelectBackground.bmp");

	GET_SINGLE(ResourceManager)->LoadSound(L"FirstBGM", L"Sound\\First.mp3", true);
	GET_SINGLE(ResourceManager)->LoadSound(L"SecondBGM", L"Sound\\Second.mp3", true);
	GET_SINGLE(ResourceManager)->LoadSound(L"ThirdBGM", L"Sound\\Third.mp3", true);
	GET_SINGLE(ResourceManager)->LoadSound(L"Select", L"Sound\\Select.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Blip", L"Sound\\Blip.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Hit", L"Sound\\Hit.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"Fire", L"Sound\\Fire.mp3", false);
	GET_SINGLE(ResourceManager)->LoadSound(L"GameOver", L"GameOver\\Blip.mp3", false);

	Image* input = new Image;
	input->SetTexture(LOAD_RES(L"Input", L"Texture\\UI\\Input.bmp"), RENDER_TYPE::TransparentBlt);
	input->SetPos({ 1320.0f, SCREEN_HEIGHT / 2.0f });
	input->SetSize({ 500.0f, 700.0f });

	GET_SINGLE(UIManager)->AddUI(L"Input", input);

	Background* bg = new Background;
	bg->SetTexture(GET_RES(L"SelectBackground"));
	AddObject(bg, LAYER::BACKGROUND);

	for (int i = 0; i < m_vecSceneNames.size(); ++i) {
		Image* img = new Image;
		img->SetTexture(GET_RES(m_vecSceneNames[i]), RENDER_TYPE::TransparentBlt);

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
			GET_SINGLE(ResourceManager)->Play(L"Blip");
			m_prevSceneIndex = m_currentSceneIndex;
			m_targetSceneIndex = max(m_currentSceneIndex - 1, 0);
			m_isChangingIndex = true;
		}
		if (GET_KEY_DOWN(KEY_TYPE::RIGHT)) {
			GET_SINGLE(ResourceManager)->Play(L"Blip");
			m_prevSceneIndex = m_currentSceneIndex;
			m_targetSceneIndex = min(m_currentSceneIndex + 1, m_vecSceneNames.size() - 1);
			m_isChangingIndex = true;
		}

		if (GET_KEY_DOWN(KEY_TYPE::SPACE)) {
			GET_SINGLE(ResourceManager)->Play(L"Select");
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
	Scene::Render(hdc);
	for (int i = 0; i < m_vecSceneImages.size(); ++i) {
		m_vecSceneImages[i]->Render(hdc);
	}
}

void SelectScene::Release() {
	m_vecSceneImages.clear();
	Scene::Release();
}
