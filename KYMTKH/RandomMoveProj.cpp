#include "pch.h"
#include "RandomMoveProj.h"
#include "TimeManager.h"
#include"CircleCollider.h"
#include"EventManager.h"

RandomMoveProj::RandomMoveProj() : Projectile() {}

RandomMoveProj::~RandomMoveProj() {}

void RandomMoveProj::Init()
{
	this->SetDir(RandomDir());
	GetComponent<CircleCollider>()->SetSize(GetSize());
}

void RandomMoveProj::Update()
{
	m_vPos += m_vDir * fDT * m_speed;
}

Vector2 RandomMoveProj::RandomDir()
{
	float angle = rand() % 360;
	float rad = angle * Deg2Rad;
	return { cos(rad), sin(rad) };
}

void RandomMoveProj::Stop()
{
	this->SetSpeed(0);
	//»ö±òº¯°æ
}

void RandomMoveProj::Remove()
{
	this->SetSpeed(m_changeSpeed);
	this->SetDir(RandomDir());
}

void RandomMoveProj::Delete()
{
	GET_SINGLE(EventManager)->DeleteObject(this);
}
