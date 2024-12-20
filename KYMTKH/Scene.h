#pragma once

#include "Object.h"

class Projectile;

class Scene {
public:
	Scene() { }
	virtual ~Scene();
public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	void AddObject(Object* obj, LAYER layer) {
		obj->Init();
		m_vecObj[(UINT)layer].push_back(obj);
	}
	void DeleteEnemyProjectiles();
public:
	const vector<Object*>& GetLayerObjects(LAYER _type) const { return m_vecObj[(UINT)_type]; }
private:
	vector<Object*> m_vecObj[(UINT)LAYER::END];
public:
	void SetIsHard(bool isHard) { m_isHard = isHard; }
protected:
	bool m_isHard = false;
};
