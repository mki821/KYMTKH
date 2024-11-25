#pragma once

class Scene;

class SceneManager {
	DECLARE_SINGLE(SceneManager)
public:
	void Init();
	void Update();
	void Render(HDC hdc);
public:
	void RegisterScene(const wstring& sceneName, std::shared_ptr<Scene> scene);
	void LoadScene(const wstring& sceneName);
public:
	const std::shared_ptr<Scene>& GetCurScene() const {
		return m_pCurrentScene;
	}
private:
	map<wstring, std::shared_ptr<Scene>> m_mapScenes;
	std::shared_ptr<Scene> m_pCurrentScene;
};

