#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "CollisionManager.h"

void CollisionManager::Update() {
	for (UINT Row = 0; Row < (UINT)LAYER::END; ++Row) {
		for (UINT Col = Row; Col < (UINT)LAYER::END; ++Col) {
			if (m_arrLayer[Row] & (1 << Col)) {
				CollisionLayerUpdate((LAYER)Row, (LAYER)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(LAYER _left, LAYER _right) {
	// �������� ������ ���ô�.
	// ���� ���� LAYER�� ������, ū ���� ��
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (m_arrLayer[Row] & (1 << Col)) {
		// üũ Ǯ��
		m_arrLayer[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else {
		m_arrLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset() {
	// �޸� �ʱ�ȭ
	memset(m_arrLayer, 0, sizeof(UINT) * (UINT)LAYER::END);
}

void CollisionManager::CollisionLayerUpdate(LAYER _left, LAYER _right) {
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLE(SceneManager)->GetCurScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->GetLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->GetLayerObjects(_right);
	map<ULONGLONG, bool>::iterator iter;

	//map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i) {
		Collider* pLeftCollider = vecLeftLayer[i]->GetComponent<Collider>();
		// �浹ü ���� ���
		if (nullptr == pLeftCollider)
			continue;

		for (size_t j = 0; j < vecRightLayer.size(); j++) {
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();

			// �浹ü�� ���ų�, �ڱ��ڽŰ��� �浹�� ���
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			COLLIDER_ID colliderID; // �� �浹ü�θ� ���� �� �ִ� ID
			colliderID.left_ID = pLeftCollider->GetID();
			colliderID.right_ID = pRightCollider->GetID();

			iter = m_mapCollisionInfo.find(colliderID.ID);

			// ���� ������ �浹�� �� ����.
			if (iter == m_mapCollisionInfo.end()) {
				// �浹 ������ �̵�ϵ� ������ ��� ���(�浹���� �ʾҴٷ�)
				m_mapCollisionInfo.insert({ colliderID.ID, false });

				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID.ID);
			}

			// �浹���� Ȯ��
			if (IsCollision(pLeftCollider, pRightCollider)) { // �������� �浹��
				if (iter->second) {
					if (vecLeftLayer[i]->GetIsDead() || vecRightLayer[j]->GetIsDead()) {
						pLeftCollider->ExitCollision(pRightCollider);
						pRightCollider->ExitCollision(pLeftCollider);
						iter->second = false;
					}
					else {
						pLeftCollider->StayCollision(pRightCollider);
						pRightCollider->StayCollision(pLeftCollider);
					}
				}
				else  { // ������ �浹 x
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead()) {
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else { // �浹 ���ϳ�? 
				if (iter->second) { // �ٵ� ������ �浹��
					pLeftCollider->ExitCollision(pRightCollider);
					pRightCollider->ExitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* left, Collider* right) {
	CircleCollider* leftC = dynamic_cast<CircleCollider*>(left);
	CircleCollider* rightC = dynamic_cast<CircleCollider*>(right);

	if (leftC == nullptr && rightC == nullptr) {
		Vector2 vLeftPos = left->GetLatedUpatedPos();
		Vector2 vRightPos = right->GetLatedUpatedPos();
		Vector2 vLeftSize = left->GetSize();
		Vector2 vRightSize = right->GetSize();

		RECT leftRt = RECT_MAKE(vLeftPos.x, vLeftPos.y, vLeftSize.x, vLeftSize.y);
		RECT rightRt = RECT_MAKE(vRightPos.x, vRightPos.y, vRightSize.x, vRightSize.y);
		RECT rt;

		return ::IntersectRect(&rt, &leftRt, &rightRt);
	}
	else if (leftC != nullptr && rightC != nullptr) {
		Vector2 vLeftPos = left->GetLatedUpatedPos();
		Vector2 vRightPos = right->GetLatedUpatedPos();
		float leftRadius = left->GetSize().x / 2.0f;
		float rightRadius = right->GetSize().x / 2.0f;

		float distance = (vLeftPos - vRightPos).Length();

		return distance <= (leftRadius + rightRadius);
	}
}