#include "pch.h"
#include "Player.h"
#include "Boss.h"
#include "CollisionManager.h"
#include "TestScene.h"

void TestScene::Init() {
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.0f, 500.0f });
	pPlayer->SetSize({ 100.0f, 100.0f });
	AddObject(pPlayer, LAYER::PLAYER);

	Object* pBoss = new Boss;
	pBoss->SetPos({ SCREEN_WIDTH / 2.0f, 200.0f });
	pBoss->SetSize({ 100.0f, 100.0f });
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}
