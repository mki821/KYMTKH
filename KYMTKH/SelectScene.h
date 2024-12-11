#pragma once

#include "Scene.h"

class Image;

class SelectScene : public Scene {
public:
	SelectScene();
public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
private:
	int m_prevSceneIndex = 0;
	float m_currentSceneIndex = 0;
	int m_targetSceneIndex = 0;
	bool m_isChangingIndex = false;
	float m_timer = 0.0f;
	vector<wstring> m_vecSceneNames;
	vector<bool> m_vecIsHard;
	vector<Image*> m_vecSceneImages;
};
