#pragma once
class RandomMoveProj;
class Boss;
class RandomMoveProjManager
{
public:
	void Spawn(int count);
	void Delete();
	void Stop();
	void Remove();
public:
	void SetOwner(Boss* obj) { m_owner =  obj; }
	void SetStopTime(float time) { m_stopTime = time; }
	void SetRemoveTime(float time) { m_removeTime = time; }
private:
	vector<RandomMoveProj*> m_projVec;
	Boss* m_owner = nullptr;
private:
	float m_stopTime = 0;
	float m_removeTime = 0;
	float m_timer = 0;
};
