#include "Stage2Scene.h"
#include "../../Game/Objcet/Player/Player.h"
#include "../../Game/Objcet/Enemy/Enemy.h"
#include "../../Framework/Input/Input.h"
#include "../../Game/Objcet/Onomatopeia/Poyon/Poyon.h"
#include "../../Game/Objcet/Onomatopeia/PataPata/PataPata.h"
#include "../../Game/Objcet/Onomatopeia/BiriBiri/BiriBiri.h"
#include "../../Framework/Component/Collider/BoxCollider2D/Collider.h"


/**
 * @brief タイトルシーンの初期化
 *
 * シーンごとに初期化は最初の一度のみ
 * →
 *
 * ステージは、縦２０マス＊横４０マス
*/

void Stage2Scene::Init(void) {
	// BGM再生
	Sound::GetInstance().Play(BGM_INGAME);


	// オブジェクトマネージャ初期化
	objectmanager.Init();
	//sound.Init();


	//-----------------------
	//-----オブジェクト追加-----
	//-----------------------
	// TODO:1218ここまで オブジェクトの管理をenumから変更→tagと名前にしたい

	// 背景
	objectmanager.AddObject<GameObject>(BACKGROUND, "Background");
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->Init(L"Game/Asset/BackGround/TitleBack.png");
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(BACKGROUND, "Background").lock()->SetScale(Vector3(1920.0f, 1080.0f, 0.0f));

	// プレイヤー
	objectmanager.AddObject<Player>(PLAYER, "Player");
	objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->Init(L"Game/Asset/Character/Player_Sprite.png", 2, 3);
	objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetPosition(Vector3(-500.0f, 600.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetScale(Vector3(130.0f, 130.0f, 0.0f));

	// 擬音銃(設計的には銃を別画像で用意してプレイヤーに持たせる方が良かったが、)
	objectmanager.AddObject<SoundGun>(UI, "SoundGun");
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->Init(L"Game/Asset/Character/CyclonImage.png", 1, 4);
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->SetPosition(Vector3(0.0f, 600.0f, 0.0f));
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->SetScale(Vector3(130.0f, 130.0f, 0.0f));
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<SoundGun>(UI, "SoundGun").second);


	//擬音（ドーン）
	objectmanager.AddObject<Poyon>(ONOMATOPOEIA, "Gion2");	// 名前要変更
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion2").lock()->Init(L"Game/Asset/Onomatopoeia/Doon.png");
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion2").lock()->SetPosition(Vector3(800.0f, 50.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion2").lock()->SetScale(Vector3(240.0f, 120.0f, 0.0f));

	// マガジン(二個持った状態でスタート、落ちてるのは一個だけ)
	// 一個目
	objectmanager.AddObject<Magazine>(UI, "Magazine1");
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine1").lock()->Init(L"Game/Asset/GameObject/Magazine.png");
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine1").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine1").lock()->SetScale(Vector3(90.0f, 90.0f, 0.0f));
	// 二個目
	objectmanager.AddObject<Magazine>(UI, "Magazine2");
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine2").lock()->Init(L"Game/Asset/GameObject/Magazine.png");
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine2").lock()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Magazine>(UI, "Magazine2").lock()->SetScale(Vector3(90.0f, 90.0f, 0.0f));

	// 二つは子オブジェクトに設定してUIに変更しておく
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<Magazine>(UI, "Magazine1").second);

	// 変更するべきこと→取得したマガジンをしっかり自身の所有オブジェクトとして設定する
	// →
	//objectmanager.GetGameObject<Player>(PLAYER, "Player").second->Set
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<Magazine>(UI, "Magazine2").second);

	// 三個目
	objectmanager.AddObject<Magazine>(OBJECT, "Magazine3");
	objectmanager.GetGameObjectPtr<Magazine>(OBJECT, "Magazine3").lock()->Init(L"Game/Asset/GameObject/Magazine.png");
	objectmanager.GetGameObjectPtr<Magazine>(OBJECT, "Magazine3").lock()->SetPosition(Vector3(400.0f, -400.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Magazine>(OBJECT, "Magazine3").lock()->SetScale(Vector3(90.0f, 90.0f, 0.0f));


	// バネ
	objectmanager.AddObject<GameObject>(OBJECT, "bane");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "bane").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "bane").lock()->SetPosition(Vector3(0.0f, -430.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "bane").lock()->SetScale(Vector3(100.0f, 70.0f, 0.0f));

	// 地面
	objectmanager.AddObject<GameObject>(GROUND, "Ground");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground").lock()->SetPosition(Vector3(0.0f, -500.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground").lock()->SetScale(Vector3(1920.0f, 120.0f, 0.0f));


	// 地面2
	objectmanager.AddObject<GameObject>(GROUND, "Ground2");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground2").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground2").lock()->SetPosition(Vector3(600.0f, -50.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground2").lock()->SetScale(Vector3(900.0f, 130.0f, 0.0f));

	// 地面3
	objectmanager.AddObject<GameObject>(GROUND, "Ground3");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground3").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground3").lock()->SetPosition(Vector3(400.0f, 40.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground3").lock()->SetScale(Vector3(300.0f, 50.0f, 0.0f));



	//擬音（ビリビリ）
	objectmanager.AddObject<BiriBiri>(ONOMATOPOEIA, "Gion");	// 名前要変更
	objectmanager.GetGameObjectPtr<BiriBiri>(ONOMATOPOEIA, "Gion").lock()->Init(L"Game/Asset/Onomatopoeia/BiriBiri.png");
	objectmanager.GetGameObjectPtr<BiriBiri>(ONOMATOPOEIA, "Gion").lock()->SetPosition(Vector3(450.0f, 60.0f, 0.0f));
	objectmanager.GetGameObjectPtr<BiriBiri>(ONOMATOPOEIA, "Gion").lock()->SetScale(Vector3(240.0f, 120.0f, 0.0f));

	// スライム
	objectmanager.AddObject<Enemy>(ENEMY, "Slime");
	objectmanager.GetGameObjectPtr<Enemy>(ENEMY, "Slime").lock()->Init(L"Game/Asset/GameObject/Slime.png");
	objectmanager.GetGameObjectPtr<Enemy>(ENEMY, "Slime").lock()->SetPosition(Vector3(200.0f, -300.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Enemy>(ENEMY, "Slime").lock()->SetScale(Vector3(80.0f, 40.0f, 0.0f));

	// クロスヘア
	objectmanager.AddObject<CrossHair>(UI, "CrossHair");
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->Init(L"Game/Asset/UI/CrossHair.png");
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->SetPosition(Vector3(200.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->SetScale(Vector3(100.0f, 100.0f, 0.0f));
	// クロスヘアをプレイヤーの子オブジェクトとして設定
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<CrossHair>(UI, "CrossHair").second);

	//enemy擬音
	objectmanager.AddObject<Poyon>(ONOMATOPOEIA, "Poyon");	// 名前要変更
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Poyon").lock()->Init(L"Game/Asset/Onomatopoeia/Poyon.png");
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Poyon").lock()->SetPosition(Vector3(500.0f, -350.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Poyon").lock()->SetScale(Vector3(240.0f, 120.0f, 0.0f));


	//サンダーエフェクト
	objectmanager.AddObject<BiriBiri>(UI, "Thunder_Effect");
	objectmanager.GetGameObjectPtr<BiriBiri>(UI, "Thunder_Effect").lock()->Init(L"Game/Asset/Effect/Thunder_Effect.png", 8, 1);
	objectmanager.GetGameObjectPtr<BiriBiri>(UI, "Thunder_Effect").lock()->SetPosition(Vector3(500.0f, 20.0f, 0.0f));
	objectmanager.GetGameObjectPtr<BiriBiri>(UI, "Thunder_Effect").lock()->SetScale(Vector3(600.0f, 1200.0f, 0.0f));
	objectmanager.GetGameObjectPtr<BiriBiri>(UI, "Thunder_Effect").lock()->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

	//マガジンの外枠
	objectmanager.AddObject<GameObject>(UI, "Frame");	// 名前要変更
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->Init(L"Game/Asset/UI/Frame.png");
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(Vector3(-900.0f, 495.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetScale(Vector3(120.0f, 80.0f, 0.0f));

	std::cout << "TitleSceneInit" << std::endl;

	std::cout << "GameSceneInit" << std::endl;

	//// UI1(ボタン)
	//objectmanager.AddObject<GameObject>(UI, "StartButton");
	//// UI2(ボタン)
	//objectmanager.AddObject<GameObject>(UI, "ExitButton");
	//// プレイヤー
	//objectmanager.AddObject<Player>(PLAYER);
}




void Stage2Scene::Update(void)
{
	Input::GetInstance().Update();
	// スティック入力値を取得
	Vector2 RightStickInput = Input::GetInstance().GetRightAnalogStick();	// 右スティック入力
	Vector2 LeftStickInput = Input::GetInstance().GetLeftAnalogStick();		// 左スティック入力

	//sound.Play(SOUND_LABEL_BGM000);


	// 入力情報の更新
	// シーン更新に必要な情報を取得
	auto grounds = objectmanager.GetObjects<GameObject>(GROUND);	// 地面(配列)
	auto grounds2 = objectmanager.GetGameObjectPtr<GameObject>(GROUND,"Ground2");
	auto playerShared = objectmanager.GetGameObject<Player>(PLAYER, "Player");
	auto playerShared2 = objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player");
	auto groundShared = objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground");
	auto groundShared2 = objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground2");
	auto enemyShared = objectmanager.GetGameObjectPtr<Enemy>(ENEMY, "Slime");
	auto gionShared = objectmanager.GetGameObjectPtr<BiriBiri>(ONOMATOPOEIA, "Gion");
	auto crosshairShared = objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair");
	auto enemygion = objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Poyon");
	auto effectShared = objectmanager.GetGameObjectPtr<GameObject>(UI, "Thunder_Effect");
	auto baneShared = objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "bane");
	auto poyonShared = objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion2");
	auto groundShared3 = objectmanager.GetGameObjectPtr<GameObject>(GROUND, "Ground3");


	effectShared.lock()->Animation(EFECT, effectShared);

	//Vector3 p_enemygion = enemygion.lock()->GetPosition();
	//p_enemygion = p_enemy;

	// 入力管理
	// 右移動
	if (Input::GetInstance().GetKeyPress(VK_D) || LeftStickInput.x > 0.1f)
	{
		objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetMoveRight(true);
		//sound.Play(SOUND_LABEL_BGM000);
		//デバック用
		//std::cout << "Playerの座標移動ができています" << std::endl;
	}
	// 左移動
	if (Input::GetInstance().GetKeyPress(VK_A) || LeftStickInput.x < -0.1f)
	{
		objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetMoveLeft(true);

		//デバック用
		//std::cout << "Playerの座標移動ができています" << std::endl;
	}
	// ジャンプ
		if (Input::GetInstance().GetKeyTrigger(VK_SPACE) || Input::GetInstance().GetButtonPress(XINPUT_GAMEPAD_A))
		{
			objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetJump(true);

			//デバック用
			//std::cout << "Playerの座標移動ができています" << std::endl;
		}
	
	//擬音の選択
	if (Input::GetInstance().GetKeyTrigger(VK_P))
	{
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();
		p_frame.x = p_frame.x + 120;
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
	}
	if (Input::GetInstance().GetKeyTrigger(VK_O))
	{
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();
		p_frame.x = p_frame.x - 120;
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
	}


	//ゲーム画面に遷移
	// シーン遷移（デバック用
	if (Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		this->ChangeScene = true;
		SetChangeScene(this->ChangeScene);
	}





	// フレーム遷移処理
	if (Input::GetInstance().GetButtonPress(XINPUT_GAMEPAD_B) || Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		Vector3 pos = playerShared.second->GetPosition();
		if (pos.x >= 850.0f)
		{
			if (pos.y <= 0.0f)
			{
				SetChangeScene(true);
				m_RequestNext = TITLE;
			}
		}
	}





	//----------------当たり判定-----------------------

	////FRAME1のPlayerとGroundの当たり判定
	//if (ColliderPlayer_Ground(playerShared, groundShared)) //Playerと一番下のGroundの当たり判定
	//{
	//	playerShared.lock()->SetOnGround(true);
	//}
	//else if (Collider_toGround(playerShared, groundShared2)) //Playerと上のGroundの当たり判定
	//{
	//	playerShared.lock()->SetOnGround(true);
	//}else if(Collider_toGround(playerShared, baneShared)) //Playerとバネの当たり判定
	//{
	//	playerShared.lock()->SetOnGround(true);
	//}


	//当たり判定
	//if (BoxCollider(playerShared.second, groundShared2.lock()))
	//{
	//	playerShared.second->SetOnGround(true);
	//	std::cout << "上のグラウンドと衝突しています" << std::endl;
	//}
	//else {
	////	playerShared.second->SetOnGround(false);
	//}


	if (ColliderPlayer_Ground(playerShared.second, grounds))
	{
		Collider_to_Object(playerShared.second, baneShared.lock());

	}
	else {
		Collider_toGround(playerShared2, grounds2.lock());

	}
	//ColliderPlayer_Ground(playerShared.second, grounds2);

	Vector3 p_enemy = enemyShared.lock()->GetPosition();


	//スライムジャンプ
	if (Collider_toGround(enemyShared, groundShared))
	{
		//スライムジャンプフラグ
		if (enemygion.lock())
		{
			if (enemygion.lock()->Get_gion() ==false)
			{

				Vector3 Slim_Position = enemygion.lock()->GetPosition();
				Slim_Position = p_enemy;
				Slim_Position.y = Slim_Position.y + 100;
				enemygion.lock()->SetPosition(Slim_Position);
			}
			else {
				Vector3 pos_bane = baneShared.lock()->GetPosition();
				baneShared.lock()->SetPosition(pos_bane);
			}

		}
		enemyShared.lock()->SetJump(true);
	}
	else if(enemygion.lock()){

		enemygion.lock()->Fade_in_out();
	}






	if (enemygion.lock() != nullptr)
	{
		Vector4 poyon_color = enemygion.lock()->GetColor(); //エラー：吸収する瞬間にenemygion自体が削除されるのでエラーが出る
		Vector3 p_poyon = p_enemy;
		p_poyon.x = p_poyon.x + 50;
		p_poyon.y = p_poyon.y + 150;
	}

	//EnemyとGroundが衝突していたら
	/*ここでエネミーのY座標の値によって画像のα値を変動させる
	例：高くなる程α値が増える*/
	/*if (!Collider_toGround(enemyShared, groundShared))
	{
		poyon_color.w += 0.05f;

		enemygion.lock()->SetColor(poyon_color);

	}
	else {

		enemyShared.lock()->SetOnGround(true);
		enemyShared.lock()->SetJump(true);
		poyon_color.w = 0.0f;
		enemygion.lock()->SetColor(poyon_color);
		enemygion.lock()->SetPosition(p_poyon);


	}*/

	Vector3 enemy_Rotation = enemyShared.lock()->GetRotation();


	if (p_enemy.x <= -300)
	{
		enemyShared.lock()->cb.matrixWorld = DirectX::XMMatrixScaling(-1.0f, 1.0f, 1.0f);
		/*ID3D11DeviceContext *deviceContext;
		deviceContext = d3d11.GetDevice();
		deviceContext->VSSetConstantBuffers(0, 1, );*/
		/*enemy_Rotation.z = 180;
		enemy_Rotation.y = 180;

		enemyShared.lock()->SetRotation(enemy_Rotation);*/
	}
	//std::cout << p_enemy.x << std::endl;


	// クロスヘアの入力取得(本来はプレイヤーのフラグを立てて、プレイヤーの更新の中でクロスヘアを動かすべき)XINPUT_GAMEPAD_RIGHT_THUMB
	if (Input::GetInstance().GetKeyPress(VK_UP) || RightStickInput.y > 0.1f)
	{
		crosshairShared.lock()->SetMoveUp(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveUp(false);
	}

	if (Input::GetInstance().GetKeyPress(VK_DOWN) || RightStickInput.y < -0.1f)
	{
		crosshairShared.lock()->SetMoveDown(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveDown(false);
	}

	if (Input::GetInstance().GetKeyPress(VK_RIGHT) || RightStickInput.x > 0.1f)
	{
		crosshairShared.lock()->SetMoveRight(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveRight(false);
	}

	if (Input::GetInstance().GetKeyPress(VK_LEFT) || RightStickInput.x < -0.1f)
	{
		crosshairShared.lock()->SetMoveLeft(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveLeft(false);
	}



	////擬音の吸収→247行目の吸い込み処理に変更、改良
	//if (Input::GetInstance().GetKeyPress(VK_F))
	//{
	//	if (ColliderFan_Gion(playerShared, gionShared))
	//	{
	//		//この下二つを一つにまとめてもいいかも？
	//		playerShared.lock()->Suction(gionShared, playerShared);
	//		//擬音の吸い込み時の回転・サイズ変更
	//		gionShared.lock()->Onomatopeia_ObjectMave(gionShared);
	//	}
	//}

	// マガジンに擬音が入っていればエイムの位置に発射
	if (Input::GetInstance().GetKeyPress(VK_W) || Input::GetInstance().GetRightTrigger())
	{
		poyonShared.lock()->Set_Onomatope(true); //擬音が発射中かのフラグ
		// マガジンに擬音が装填されているかチェック
		if (playerShared.second->GetLoadedBullet())
		{
			playerShared.second->SetIsShot(true);


			//--------------------------------------
			//			擬音のタグ変更処理
			//--------------------------------------

			// ここオブジェクトマネージャから擬音の情報持ってきたほうが良いかも？

			// ここで擬音のタグをUIから擬音に変更
			// →擬音のポインタだけわかってるのにキーの特定がスムーズにできないのでやっぱり管理方法変えたほうがいい(登録されてるタグを毎フレーム確認して同期させるとか)

			// ここでは持ってきた擬音がキャストできた型によってその擬音のタグを変えるようにする
			auto bullet = playerShared.second->GetLoadedBullet();

			// 擬音が"パタパタ"の場合
			if (dynamic_cast<PataPata*>(bullet))
			{
				objectmanager.ChangeTag(UI, "PataPata", ONOMATOPOEIA);
			}
			// "ビリビリ"の場合
			else if (dynamic_cast<BiriBiri*>(bullet))
			{
				objectmanager.ChangeTag(UI, "BiriBiri", ONOMATOPOEIA);
			}
			// "ポヨン"の場合
			else if (dynamic_cast<Poyon*>(bullet))
			{
				objectmanager.ChangeTag(UI, "Poyon", ONOMATOPOEIA);
			}
			// それ以外(不明な型)の場合
			else
			{
				throw std::runtime_error("擬音をキャストできませんでした");
			}
			// SE再生
			Sound::GetInstance().Play(SE_SHOT);
		}
	}
	//playerShared.lock()->Shot(gionShared);

	/*if (poyonShared.lock() == nullptr)
	{

		std::cout << "nullptr" << std::endl;
	}
	else {
		if (poyonShared.lock()->Get_Onomatope())
		{
			auto poyonshared = objectmanager.GetGameObject<Poyon>(ONOMATOPOEIA, "Poyon");
			poyonshared.second->Action();

			if (BoxCollider(poyonshared.second, baneShared.lock()))
			{
			}
		}
	}*/
	

	Vector3 _p_biribiri = effectShared.lock()->GetPosition(); //ポヨンの座標
	Vector3 _r_biribiri = effectShared.lock()->GetRotation();  //ポヨンの回転


	// ----------------吸い込み処理→ここはプレイヤーの処理に移す-------------------------
	// プレイヤー発の扇型と当たってる擬音を探す→(一番近くの)当たってる擬音を吸い込む
	if (Input::GetInstance().GetKeyPress(VK_F) || Input::GetInstance().GetLeftTrigger())
	{
		// 吸い込める擬音を探す
		// そのフレーム内のタグが擬音のもの全て取得→それとプレイヤーから出る扇型の当たり判定を取得
		//auto onomatopoeias = objectmanager.GetObjects<IOnomatopoeia>(ONOMATOPOEIA);
		auto onomatopoeias = objectmanager.GetGameObjectPair<IOnomatopoeia>(ONOMATOPOEIA);

		// 擬音が0ではなければ
		if (!onomatopoeias.empty())
		{
			// 扇形との当たり判定を取得
			auto HitOnomatopoeia = ColliderFan_Gion(playerShared.second, onomatopoeias);

			// ポインタに値が入っていれば(扇形範囲内に当たった擬音があれば)
			if (HitOnomatopoeia.second)
			{
				// 擬音の吸い込み実行
				playerShared.second->SetIsSuction(true);			// プレイヤーの状態を吸い込み中に設定

				// 吸い込み処理が終わったら
				if (playerShared.second->Suction(HitOnomatopoeia.second))
				{
					// 吸い込み処理が終わった時に擬音のタグをUIに変更、射撃するときにタグを擬音に変更する処理がまだ
					objectmanager.ChangeTag(HitOnomatopoeia.first.first, HitOnomatopoeia.first.second, UI);
					/*enemygion.lock()->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
					gionShared.lock()->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));*/
				}
			}
			// 擬音が0(吸い込み中に扇型範囲から擬音がいなくなった場合)
			else
			{
				// プレイヤーの状態を変更
				playerShared.second->SetIsSuction(false);		// 「非」吸い込み中に設定

			}
		}
		// 擬音が0(フレーム内の擬音がない場合)
		else
		{
			// プレイヤーの状態を変更
			playerShared.second->SetIsSuction(false);		// 「非」吸い込み中に設定
		}
	}
	//連：メモ
	//擬音を回収したときに、オブジェクトをただ移動させるだけじゃなくて、回収したオブジェクトの情報によって表示させるUIを変える



	//enemygionがemptyでないかチェック
	if (enemygion.lock())
	{
		//ポヨンの画像とバネの画像が当たっているか
		if (BoxCollider(enemygion.lock(), baneShared.lock()))
		{

			enemygion.lock()->Set_gion(true);
			Vector3 _p_poyon = baneShared.lock()->GetPosition(); //ポヨンの座標
			Vector3 _r_poyon = baneShared.lock()->GetRotation();  //ポヨンの回転
			enemygion.lock()->Set_Onomatope(true); //当たってたらフラグをtrue
			_p_poyon.x = _p_poyon.x + 30;
			_p_poyon.y = _p_poyon.y + 20;
			_r_poyon.z = _r_poyon.z - 15;
			enemygion.lock()->SetPosition(_p_poyon); //ポヨンの画像の座標をバネにくっつける
			enemygion.lock()->SetRotation(_r_poyon); //ポヨンの画像の回転を更新
			std::cout << "当りました" << std::endl;
		}
		else
		{
			//std::cout << "当たっていません" << std::endl;
		}
	
		//二回目の回収をするまではずっとtrue
		if (enemygion.lock()->Get_Onomatope())
		{
			enemygion.lock()->Fade_in_out();
			//Playerと付与したオブジェクトが当たっているか
			if (BoxCollider(playerShared.second, baneShared.lock()))
			{
				enemygion.lock()->Action(playerShared.second); //当たっていればAction関数実行
			}
		}
	}
	else {
		std::cout << "enemygionがemptyです" << std::endl;
	}

	//ビリビリ
	if (gionShared.lock())
	{
		if (BoxCollider(gionShared.lock(), effectShared.lock()))
		{
			effectShared.lock()->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			//_p_biribiri.x = _p_biribiri.x - 250;
			//_p_biribiri.y = _p_biribiri.y + 80;
			//_r_biribiri.z = _r_biribiri.z - 15;
			gionShared.lock()->Set_Onomatope(true); //当たってたらフラグをtrue
			//
			//gionShared.lock()->SetPosition(_p_biribiri); //ポヨンの画像の座標をバネにくっつける
			//gionShared.lock()->SetRotation(_r_biribiri); //ポヨンの画像の回転を更新
			std::cout << "当りました" << std::endl;
		}
		else {
			effectShared.lock()->SetColor(Color(1.0f, 1.0f, 1.0f, 0.0f)); //ビリビリのエフェクトを色で消えた感じにしてる
		}

		gionShared.lock()->Fade_in_out();
		//二回目の回収をするまではずっとtrue
		if (gionShared.lock()->Get_Onomatope())
		{
			//Playerと付与したオブジェクトが当たっているか
			if (BoxCollider(playerShared.second, groundShared3.lock()))
			{
				playerShared.second->SetOnGround(true);
				gionShared.lock()->Action(playerShared.second); //当たっていればAction関数実行
			}
			else {
				Vector3 r_player = playerShared.second->GetRotation();
				r_player.z = 0;
				playerShared.second->SetRotation(r_player);
			}
		}
	}


	// ここでマガジンがUIになっていなければ当たり判定を取りたい
	if (m_MagCount >= 1)
	{
		// １つのシーンに落ちてるマガジン数は一個なので、シーンの持つマガジンカウントが１ならまだ当たっていない
		// →判定チェックする

		auto magShared = objectmanager.GetGameObject<Magazine>(OBJECT, "Magazine3");

		// マガジンと地面
		Collider_toGround(std::weak_ptr<Magazine>(magShared.second), groundShared);
		// プレイヤーとマガジンが当たったら
		if (Collider_Player_to_Magazine(playerShared.second, objectmanager.GetGameObjectPtr<Magazine>(OBJECT, "Magazine3")))
		{
			// マガジンのタグを変更
			objectmanager.ChangeTag(magShared.first.first, magShared.first.second, UI);
			// プレイヤーの子オブジェクトに設定
			playerShared.second->SetChild(magShared.second);
			/*magShared.second->SetScale(Vector3(75.0f, 75.0f, 0.0f));
			magShared.second->SetPosition(Vector3(-800.0f, -500.0f, 0.0f));*/
			m_MagCount = 0;
		}

	}


	/////////////////////////////////
	// カーソル移動して擬音の選択
	/////////////////////////////////

	// R1でマガジンカーソル右移動
	if (Input::GetInstance().GetKeyTrigger(VK_P) || Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		// カーソルの座標取得
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();

		// ドォン用マガジンを除く一番最後のマガジンを選択していなければ
		if (playerShared.second->GetMagNumber() != playerShared.second->GetMagCount() - 1)
		{
			// マガジン選択番号を１増やして
			playerShared.second->SetMagNumber(playerShared.second->GetMagNumber() + 1);
			// カーソルを右に移動
			p_frame.x += 120.0f;
		}
		// 一番最後のマガジンを選択している場合
		else
		{
			// マガジン選択番号を１(ドォン用マガジンを除く一番最初)に戻して
			playerShared.second->SetMagNumber(1);
			// カーソルを初期位置に移動
			p_frame.x = -900.0f;
		}
		// 座標を設定
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}
	// L1でマガジンカーソル左移動
	if (Input::GetInstance().GetKeyTrigger(VK_O) || Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		// カーソルの座標取得
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();

		// ドォン用マガジンを除く一番最初のマガジンを選択していなければ
		if (playerShared.second->GetMagNumber() != 1)
		{
			Sound::GetInstance().Play(SE_CLICK);
			// マガジン選択番号を１減らして
			playerShared.second->SetMagNumber(playerShared.second->GetMagNumber() - 1);
			// カーソルを左に移動
			p_frame.x -= 120.0f;
		}
		// 一番最初のマガジンを選択している場合
		else
		{
			// マガジン選択用カーソルを取得
			auto magcursor = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock();
			// マガジン選択番号を(ドォン用マガジンを除く)一番後ろにして
			playerShared.second->SetMagNumber(playerShared.second->GetMagCount() - 1);
			// カーソルを一番後ろの位置に移動
			p_frame.x = -900.0f + magcursor->GetScale().x * (playerShared.second->GetMagCount() - 2);	// 初期位置 + カーソルの大きさ * マガジン数(ドォン入れないので-2)
		}
		// 座標を設定
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}
	// マガジンとの当たり判定を毎フレーム取る→マガジンを取得したらその判定チェックはしなくておｋ
	//objectmanager.Collider_Player_to_Object();		// ここで当たったらマガジン数を１つ減らす



	// R1でマガジンカーソル右移動
	if (Input::GetInstance().GetKeyTrigger(VK_P) || Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		// カーソルの座標取得
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();

		// ドォン用マガジンを除く一番最後のマガジンを選択していなければ
		if (playerShared.second->GetMagNumber() != playerShared.second->GetMagCount() - 1)
		{
			// マガジン選択番号を１増やして
			playerShared.second->SetMagNumber(playerShared.second->GetMagNumber() + 1);
			// カーソルを右に移動
			p_frame.x += 120.0f;
		}
		// 一番最後のマガジンを選択している場合
		else
		{
			// マガジン選択番号を１(ドォン用マガジンを除く一番最初)に戻して
			playerShared.second->SetMagNumber(1);
			// カーソルを初期位置に移動
			p_frame.x = -900.0f;
		}
		// 座標を設定
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}
	// L1でマガジンカーソル左移動
	if (Input::GetInstance().GetKeyTrigger(VK_O) || Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER))
	{
		// カーソルの座標取得
		Vector3 p_frame = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->GetPosition();

		// ドォン用マガジンを除く一番最初のマガジンを選択していなければ
		if (playerShared.second->GetMagNumber() != 1)
		{
			Sound::GetInstance().Play(SE_CLICK);
			// マガジン選択番号を１減らして
			playerShared.second->SetMagNumber(playerShared.second->GetMagNumber() - 1);
			// カーソルを左に移動
			p_frame.x -= 120.0f;
		}
		// 一番最初のマガジンを選択している場合
		else
		{
			// マガジン選択用カーソルを取得
			auto magcursor = objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock();
			// マガジン選択番号を(ドォン用マガジンを除く)一番後ろにして
			playerShared.second->SetMagNumber(playerShared.second->GetMagCount() - 1);
			// カーソルを一番後ろの位置に移動
			p_frame.x = -900.0f + magcursor->GetScale().x * (playerShared.second->GetMagCount() - 2);	// 初期位置 + カーソルの大きさ * マガジン数(ドォン入れないので-2)
		}
		// 座標を設定
		objectmanager.GetGameObjectPtr<GameObject>(UI, "Frame").lock()->SetPosition(p_frame);
		// SE再生
		Sound::GetInstance().Play(SE_CLICK);
	}




	objectmanager.Update();

}

void Stage2Scene::Draw(void) {
	objectmanager.Draw();
}

void Stage2Scene::Uninit(void) {
	objectmanager.Uninit();
	//sound.Uninit();

}
