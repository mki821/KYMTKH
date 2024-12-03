#pragma once

class Component;
class Collider;

class Object {
public:
	Object();
	virtual ~Object();
public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc) abstract;
	virtual void ComponentRender(HDC hdc);
public:
	template<typename T> void AddComponent() {
		T* component = new T;
		component->SetOwner(this);
		m_vecComponents.push_back(component);
	}
	template<typename T> T* GetComponent() {
		T* component = nullptr;
		for (Component* compo : m_vecComponents) {
			component = dynamic_cast<T*>(compo);

			if (component) break;
		}
		return component;
	}
protected:
	void Wait(float second, std::function<void()> func);
private:
	vector<std::pair<float, std::function<void()>>> m_vecWaitFuncs;
	vector<std::pair<float, std::function<void()>>> m_vecAdditionalWaitFuncs;
public:
	void SetPos(Vector2 vPos) { m_vPos = vPos; }
	void SetSize(Vector2 vSize) { m_vSize = vSize; }
	const Vector2& GetPos() const { return m_vPos; }
	const Vector2& GetSize() const { return m_vSize; }
protected:
	Vector2 m_vPos;
	Vector2 m_vSize;
private:
	vector<Component*> m_vecComponents;
public:
	virtual void EnterCollision(Collider* other);
	virtual void StayCollision(Collider* other);
	virtual void ExitCollision(Collider* other);
	const bool& GetIsDead() const { return m_isDie; }
	void SetDead() { m_isDie = true; }
protected:
	bool m_isDie = false;
};
