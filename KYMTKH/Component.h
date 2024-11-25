#pragma once

class Object;

class Component {
public:
	Component() : m_pOwner(nullptr) { }
	virtual ~Component() { }
public:
	virtual void LateUpdate() abstract;
	virtual void Render(HDC hdc) abstract;
public:
	void SetOwner(Object* owner) { m_pOwner = owner; }
	Object* GetOwner() const { return m_pOwner; }
protected:
	Object* m_pOwner;
};
