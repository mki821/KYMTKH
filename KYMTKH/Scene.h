#pragma once

class Object;

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
		m_vecObj[(UINT)layer].push_back(obj);
	}
public:
	const vector<Object*>& GetLayerObjects(LAYER _type) const { return m_vecObj[(UINT)_type]; }
private:
	vector<Object*> m_vecObj[(UINT)LAYER::END];
};
