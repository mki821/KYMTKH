#include "pch.h"
#include "UIManager.h"
#include "Image.h"
#include "Player.h"
#include "JHBoss.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "TestScene.h"

void TestScene::Init() {
	for (int i = 1; i <= 5; ++i) {
		Image* heart = new Image;
		heart->SetPos({ 1330.0f, SCREEN_HEIGHT - 60.0f * i - 70.0f });

		wstring name = std::format(L"Heart_{0}", i);
		GET_SINGLE(UIManager)->AddUI(name, heart);
	}

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.0f, 900.0f });
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

void TestScene::Release() {
	GET_SINGLE(UIManager)->Clear();
}
