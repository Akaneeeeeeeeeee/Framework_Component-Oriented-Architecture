#include "TitleScene.h"
#include "../../Framework/Input/Input.h"
#include "../../Framework/ResourceManager/ResourceManager.h"
#include "../../Framework/Component/Renderer/SpriteRenderer/SpriteRenderer.h"

void TitleScene::Init(void) {
	Sound::GetInstance().Play(BGM_TITLE);

	// 背景
	objectmanager.AddObject<Player>(ENEMY, "player");
	objectmanager.GetGameObject<Player>("player")->Init();
	objectmanager.GetGameObject<Player>("player")->AddComponent<SpriteRenderer>()->SetTexture(TextureID::TITLEBACK, { 1,1 });
	objectmanager.GetGameObject<Player>("player")->GetComponent<TransformComponent>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObject<Player>("player")->AddComponent<TransformComponent>()->SetScale(Vector3(1920.0f, 1080.0f, 0.0f));

	//タイトルロゴ
	objectmanager.AddObject<Player>(UI, "TitleLogo");
	objectmanager.GetGameObject<Player>("TitleLogo")->Init();
	objectmanager.GetGameObject<Player>("TitleLogo")->AddComponent<SpriteRenderer>()->SetTexture(TextureID::TITLEBACK, { 1,1 });
	objectmanager.GetGameObject<Player>("TitleLogo")->GetComponent<TransformComponent>()->SetPosition(Vector3(-400.0f, 300.0f, 0.0f));
	objectmanager.GetGameObject<Player>("TitleLogo")->GetComponent<TransformComponent>()->SetScale(Vector3(1400.0f, 900.0f, 0.0f));
	Vector3 r_rotation = objectmanager.GetGameObject<Player>("TitleLogo")->GetComponent<TransformComponent>()->GetRotation();
	r_rotation.z = 15.0f;
	objectmanager.GetGameObject<Player>("TitleLogo")->GetComponent<TransformComponent>()->SetRotation(r_rotation);

	//startロゴ
	objectmanager.AddObject<Object>(UI, "start");
	objectmanager.GetGameObject<Object>("start")->AddComponent<SpriteRenderer>()->SetTexture(TextureID::BUTTON_START, { 2,1 });
	objectmanager.GetGameObject<Object>("start")->GetComponent<TransformComponent>()->SetPosition(Vector3(500.0f, -150.0f, 0.0f));
	objectmanager.GetGameObject<Object>("start")->GetComponent<TransformComponent>()->SetScale(Vector3(500.0f, 400.0f, 0.0f));

	//endロゴ
	objectmanager.AddObject<Object>(UI, "end");
	objectmanager.GetGameObject<Object>("end")->AddComponent<SpriteRenderer>()->SetTexture(TextureID::BUTTON_END, { 2,1 });
	objectmanager.GetGameObject<Object>("end")->GetComponent<TransformComponent>()->SetPosition(Vector3(500.0f, -350.0f, 0.0f));
	objectmanager.GetGameObject<Object>("end")->GetComponent<TransformComponent>()->SetScale(Vector3(500.0f, 400.0f, 0.0f));

	// カーソル
	objectmanager.AddObject<Object>(UI, "Cursol");
	objectmanager.GetGameObject<Object>("Cursol")->AddComponent<SpriteRenderer>()->SetTexture(TextureID::CURSOR_CHARACTER, { 2,0 });
	objectmanager.GetGameObject<Object>("Cursol")->GetComponent<TransformComponent>()->SetPosition(Vector3(300.0f, -170.0f, 0.0f));
	objectmanager.GetGameObject<Object>("Cursol")->GetComponent<TransformComponent>()->SetScale(Vector3(300.0f, 450.0f, 0.0f));

	//キャラクターロゴ
	/*objectmanager.AddObject<Object>(UI, "PlayerLogo");
	objectmanager.GetGameObject<Object>(UI, "PlayerLogo")()->Init(L"Game/Asset/Character/Player.png");
	objectmanager.GetGameObject<Object>(UI, "PlayerLogo")()->SetPosition(Vector3(-400.0f, -300.0f, 0.0f));
	objectmanager.GetGameObject<Object>(UI, "PlayerLogo")()->SetScale(Vector3(800.0f, 900.0f, 0.0f));
	Vector3 c_rotation = objectmanager.GetGameObject<Object>(UI, "PlayerLogo")()->GetRotation();
	c_rotation.z = 15.0f;
	objectmanager.GetGameObject<Object>(UI, "PlayerLogo")()->SetRotation(c_rotation);*/

	std::cout << "TitleSceneInit" << std::endl;
}

void TitleScene::Update(void) {
	// 入力情報の更新
	Input::GetInstance().Update();

	// スティック入力値を取得
	Vector2 RightStickInput = Input::GetInstance().GetRightAnalogStick();	// 右スティック入力
	Vector2 LeftStickInput = Input::GetInstance().GetLeftAnalogStick();		// 左スティック入力
	
	Vector3 Cursol_pos = objectmanager.GetGameObject<Object>("Cursol")->GetComponent<TransformComponent>()->GetPosition();
	
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
		objectmanager.GetGameObject<Object>("Cursol")->GetComponent<TransformComponent>()->SetPosition(Cursol_pos);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}

	// 上ボタン入力確認
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) || Input::GetInstance().GetKeyPress(VK_UP))
	{
		Cursol_pos.y = -170.0f;
		objectmanager.GetGameObject<Object>("Cursol")->GetComponent<TransformComponent>()->SetPosition(Cursol_pos);
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
void TitleScene::Title_Onomatope_Move(std::weak_ptr<Object>_onomatope,float deltaTime)
{
	
}
