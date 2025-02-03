#include "ResultScene.h"
#include "../../Framework/Input/Input.h"

void ResultScene::Init(void) {
	// オブジェクト追加
	objectmanager.AddObject<Player>(ENEMY, "player");
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->Init(L"Game/Asset/BackGround/GAME_OVER.png");
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->SetScale(Vector3(1960.0f, 1080.0f, 0.0f));

	objectmanager.AddObject<GameObject>(UI, "STAGE1");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->Init(L"Game/Asset/UI/STAGE_REVERS.png");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetPosition(Vector3(0.0f, -200.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetScale(Vector3(330.0f, 130.0f, 0.0f));

	objectmanager.AddObject<GameObject>(UI, "STAGE2");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->Init(L"Game/Asset/UI/TITLE_REVERS.png");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->SetPosition(Vector3(0.0f, -400.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->SetScale(Vector3(330.0f, 130.0f, 0.0f));

	std::cout << "ResultSceneInit" << std::endl;
}


void ResultScene::Update(void) {
	Input::GetInstance().Update();
	//ゲーム画面に遷移
	// シーン遷移（デバック用
	if (Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		this->ChangeScene = true;
		SetChangeScene(this->ChangeScene);
	}
}


void ResultScene::Draw(void) {
	objectmanager.Draw();
}


void ResultScene::Uninit(void) {

}