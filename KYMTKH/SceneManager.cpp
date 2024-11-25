#include "pch.h"
#include "Scene.h"
#include "TestScene.h"
#include "SceneManager.h"

void SceneManager::Init() {
	m_pCurrentScene = nullptr;

	RegisterScene(L"TestScene", std::make_shared<TestScene>());

	LoadScene(L"TestScene");
}

void SceneManager::Update() {
	if (m_pCurrentScene == nullptr) return;

	m_pCurrentScene->Update();
	m_pCurrentScene->LateUpdate();
}

void SceneManager::Render(HDC hdc) {
	if (m_pCurrentScene == nullptr) return;

	m_pCurrentScene->Render(hdc);
}

void SceneManager::RegisterScene(const wstring& sceneName, std::shared_ptr<Scene> scene) {
	if (sceneName.empty() || scene == nullptr) return;

	m_mapScenes.insert(m_mapScenes.end(), { sceneName, scene });

	if (m_pCurrentScene == nullptr)
		LoadScene(sceneName);
}

void SceneManager::LoadScene(const wstring& sceneName) {
	if (m_pCurrentScene != nullptr) {
		m_pCurrentScene->Release();
		m_pCurrentScene = nullptr;
	}

	auto iter = m_mapScenes.find(sceneName);
	if (iter != m_mapScenes.end()) {
		m_pCurrentScene = iter->second;
		m_pCurrentScene->Init();
	}
}
