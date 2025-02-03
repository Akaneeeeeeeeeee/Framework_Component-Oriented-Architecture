#include "StageSelectScene.h"
#include "../../Framework/Input/Input.h"
#include "../../Game/SceneManager/SceneManager.h"



void StageSelectScene::Init(void) {
	Sound::GetInstance().Play(BGM_STAGESELECT);

	// 背景
	objectmanager.AddObject<GameObject>(BACKGROUND, "Background");
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->Init(L"Game/Asset/BackGround/StageSelectBack.png");
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->SetScale(Vector3(1920.0f, 1080.0f, 0.0f));
	
	// ステージ1ボタン
	objectmanager.AddObject<GameObject>(UI, "STAGE1");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->Init(L"Game/Asset/UI/Stage1Button.png", 2, 1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetScale(Vector3(500.0f, 400.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetUV(Int2(1, 0));		// 最初はステージ1を選択中

	// 通常時ピンク選択中黄色
	// ステージ2ボタン
	objectmanager.AddObject<GameObject>(UI, "STAGE2");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->Init(L"Game/Asset/UI/Stage2Button.png", 2, 1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->SetPosition(Vector3(0.0f, -300.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->SetScale(Vector3(500.0f, 400.0f, 0.0f));

	// カーソル
	objectmanager.AddObject<GameObject>(UI, "Cursol");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->Init(L"Game/Asset/UI/TitleCursol.png", 3, 1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Vector3(-250.0f, -10.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetScale(Vector3(300.0f, 450.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetUV(Int2(2, 0));


	std::cout << "STAGE1_SCENEInit" << std::endl;
}

void StageSelectScene::Update(void) {
	Input::GetInstance().Update();

	//ゲーム画面に遷移
	// シーン遷移（デバック用

	Vector3 Cursor_pos = objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->GetPosition();
	Int2 Stage1Button_UV = objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->GetUV();
	Int2 Stage2Button_UV = objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->GetUV();


	// スタートボタン入力取得
	// (デバッグ用)エンターキー入力取得
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_START) || Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		// カーソル位置が上の場合
		if (Cursor_pos.y == -10.0f)
		{
			// 遷移先シーンをステージに設定
			m_RequestNext = STAGE2;
		}
		
		// カーソル位置が下の場合
		if (Cursor_pos.y == -300.0f)
		{
			// 遷移先をステージ2に設定
			m_RequestNext = STAGE2;
		}
		// シーン遷移フラグを立てる
		SetChangeScene(true);
		// BGM停止
		Sound::GetInstance().Stop(BGM_STAGESELECT);
	}
	else
	{
		// シーン遷移フラグを立てる
		SetChangeScene(false);
	}


	
	
	//////////////////////////////////
	//			カーソル移動
	//////////////////////////////////
	
	// 下ボタン入力確認
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetInstance().GetKeyPress(VK_DOWN))
	{
		Cursor_pos.y -= 300.0f;
		if (Cursor_pos.y < -300.0f)
		{
			Cursor_pos.y = -300.0f;
		}
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Cursor_pos);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}

	// 上ボタン入力確認
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || Input::GetInstance().GetKeyPress(VK_UP))
	{
		Cursor_pos.y += 300.0f;
		if (Cursor_pos.y > -10.0f)
		{
			Cursor_pos.y = -10.0f;
		}
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Cursor_pos);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}
	
	// カーソル座標によってボタンの色を変化
	// ステージ1選択中の場合
	if (Cursor_pos.y == 0.0f)
	{
		// ステージ1ボタンの画像を変化
		Stage1Button_UV.x = 1;	// ステージ1を選択中に
		Stage2Button_UV.x = 0;	// ステージ2を通常時に
	}
	// ステージ2選択中の場合
	else if (Cursor_pos.y == -300.0f)
	{
		// ステージ1ボタンの画像を変化
		Stage1Button_UV.x = 0;	// ステージ1を通常時に
		Stage2Button_UV.x = 1;	// ステージ2を選択中に
	}
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE1").lock()->SetUV(Stage1Button_UV);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "STAGE2").lock()->SetUV(Stage2Button_UV);
}



void StageSelectScene::Draw(void) {
	objectmanager.Draw();
}

void StageSelectScene::Uninit(void) {
	// BGM停止
	Sound::GetInstance().Stop(BGM_STAGESELECT);
	objectmanager.Uninit();
}

