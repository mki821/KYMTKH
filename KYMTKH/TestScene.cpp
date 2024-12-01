#include "pch.h"
#include "Player.h"
#include "JHBoss.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "TestScene.h"

void TestScene::Init() {
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.0f, 500.0f });
	pPlayer->SetSize({ 15.0f, 15.0f });
	AddObject(pPlayer, LAYER::PLAYER);

	Boss* pBoss = new JHBoss;
	pBoss->SetPos({ SCREEN_WIDTH / 2.0f, 200.0f });
	pBoss->SetSize({ 30.0f, 30.0f });
	pBoss->SetPlayer(dynamic_cast<Player*>(pPlayer));
	pBoss->GetComponent<Collider>()->SetSize(pBoss->GetSize());
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}
