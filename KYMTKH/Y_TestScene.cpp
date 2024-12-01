#include "pch.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Y_TestScene.h"
#include"FirstBoss.h"

void Y_TestScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.0f, 500.0f });
	pPlayer->SetSize({ 100.0f, 100.0f });
	AddObject(pPlayer, LAYER::PLAYER);
	SetPlayer(pPlayer);

	Object* pBoss = new FirstBoss;
	pBoss->SetPos({ SCREEN_WIDTH / 2.0f, 200.0f });
	pBoss->SetSize({ 100.0f, 100.0f });
	pBoss->GetComponent<Collider>()->SetSize(pBoss->GetSize());
	AddObject(pBoss, LAYER::ENEMY);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY_PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::PLAYER_PROJECTILE);
}
