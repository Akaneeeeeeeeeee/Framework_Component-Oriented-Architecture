#include "TitleScene.h"
#include "../../Framework/Input/Input.h"



void TitleScene::Init(void) {
	Sound::GetInstance().Play(BGM_TITLE);

	// 背景
	objectmanager.AddObject<Player>(ENEMY, "player");
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->Init(L"Game/Asset/BackGround/TitleBack.png");
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Player>(ENEMY, "player").lock()->SetScale(Vector3(1920.0f, 1080.0f, 0.0f));

	//タイトルロゴ
	objectmanager.AddObject<Player>(UI, "TitleLogo");
	objectmanager.GetGameObjectPtr<Player>(UI, "TitleLogo").lock()->Init(L"Game/Asset/UI/TitleLogo.png");
	objectmanager.GetGameObjectPtr<Player>(UI, "TitleLogo").lock()->SetPosition(Vector3(-400.0f, 300.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Player>(UI, "TitleLogo").lock()->SetScale(Vector3(1400.0f, 900.0f, 0.0f));
	Vector3 r_rotation = objectmanager.GetGameObjectPtr<Player>(UI, "TitleLogo").lock()->GetRotation();
	r_rotation.z = 15.0f;
	objectmanager.GetGameObjectPtr<Player>(UI, "TitleLogo").lock()->SetRotation(r_rotation);

	//startロゴ
	objectmanager.AddObject<GameObject>(UI, "start");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "start").lock()->Init(L"Game/Asset/UI/StartButton.png",2.1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "start").lock()->SetPosition(Vector3(500.0f, -150.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "start").lock()->SetScale(Vector3(500.0f, 400.0f, 0.0f));

	//endロゴ
	objectmanager.AddObject<GameObject>(UI, "end");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "end").lock()->Init(L"Game/Asset/UI/EndButton.png", 2.1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "end").lock()->SetPosition(Vector3(500.0f, -350.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "end").lock()->SetScale(Vector3(500.0f, 400.0f, 0.0f));

	// カーソル
	objectmanager.AddObject<GameObject>(UI, "Cursol");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->Init(L"Game/Asset/UI/CharacterCursor.png", 3.1);
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetUV(Int2(2, 0));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Vector3(300.0f, -170.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetScale(Vector3(300.0f, 450.0f, 0.0f));

	//キャラクターロゴ
	objectmanager.AddObject<GameObject>(UI, "PlayerLogo");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "PlayerLogo").lock()->Init(L"Game/Asset/Character/Player.png");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "PlayerLogo").lock()->SetPosition(Vector3(-400.0f, -300.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "PlayerLogo").lock()->SetScale(Vector3(800.0f, 900.0f, 0.0f));
	Vector3 c_rotation = objectmanager.GetGameObjectPtr<GameObject>(UI, "PlayerLogo").lock()->GetRotation();
	c_rotation.z = 15.0f;
	objectmanager.GetGameObjectPtr<GameObject>(UI, "PlayerLogo").lock()->SetRotation(c_rotation);

	std::cout << "TitleSceneInit" << std::endl;
}

void TitleScene::Update(void) {
	// 入力情報の更新
	Input::GetInstance().Update();

	// スティック入力値を取得
	Vector2 RightStickInput = Input::GetInstance().GetRightAnalogStick();	// 右スティック入力
	Vector2 LeftStickInput = Input::GetInstance().GetLeftAnalogStick();		// 左スティック入力
	
	Vector3 Cursol_pos = objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->GetPosition();

	
	// ゲームセレクト画面に遷移
	// シーン遷移（デバック用
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_START) || Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		// カーソル位置が上の場合
		if (Cursol_pos.y == -170.0f)
		{
			// 遷移先シーンをステージ選択に設定
			m_RequestNext = STAGESELECT;
		}

		// カーソル位置が下の場合
		if (Cursol_pos.y == -370.0f)
		{
			// 遷移先をゲーム終了に設定
			m_RequestNext = QUIT;
		}
		// シーン遷移フラグを立てる
		SetChangeScene(true);
		// BGM停止
		Sound::GetInstance().Stop(BGM_TITLE);
	}
	else
	{
		// シーン遷移フラグを立てる
		SetChangeScene(false);
	}

	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) || Input::GetInstance().GetKeyPress(VK_DOWN))
	{
		Cursol_pos.y = -370.0f;
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Cursol_pos);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}

	// 上ボタン入力確認
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || Input::GetInstance().GetKeyPress(VK_UP))
	{
		Cursol_pos.y = -170.0f;
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Cursol").lock()->SetPosition(Cursol_pos);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}
}

void TitleScene::Draw(void) {
	objectmanager.Draw();
}

void TitleScene::Uninit(void) {
	
	objectmanager.Uninit();
}

//オノマトペのMove関数
void TitleScene::Title_Onomatope_Move(std::weak_ptr<GameObject>_onomatope,float deltaTime)
{
	
}
