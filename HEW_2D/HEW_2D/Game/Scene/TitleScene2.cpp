#include "TitleScene.h"
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
void TitleScene::Init(void) {
	// オブジェクトマネージャ初期化
	objectmanager.Init();


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
	objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetPosition(Vector3(0.0f, 600.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetScale(Vector3(130.0f, 130.0f, 0.0f));

	// 擬音銃(設計的には銃を別画像で用意してプレイヤーに持たせる方が良かったが、)
	objectmanager.AddObject<SoundGun>(UI, "SoundGun");
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->Init(L"Game/Asset/Character/Cyclon.png", 4, 1);
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->SetPosition(Vector3(0.0f, 600.0f, 0.0f));
	objectmanager.GetGameObjectPtr<SoundGun>(UI, "SoundGun").lock()->SetScale(Vector3(130.0f, 130.0f, 0.0f));
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<SoundGun>(UI, "SoundGun").second);


	//擬音（どおん）
	objectmanager.AddObject<Poyon>(ONOMATOPOEIA, "Gion");	// 名前要変更
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion").lock()->Init(L"Game/Asset/Onomatopoeia/BiriBiri.png");
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion").lock()->SetPosition(Vector3(500.0f, -350.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion").lock()->SetScale(Vector3(240.0f, 120.0f, 0.0f));

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


	// 地面
	objectmanager.AddObject<GameObject>(OBJECT, "Ground");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground").lock()->SetPosition(Vector3(0.0f, -500.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground").lock()->SetScale(Vector3(1920.0f, 120.0f, 0.0f));

	// 地面2
	objectmanager.AddObject<GameObject>(OBJECT, "Ground2");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground2").lock()->Init(L"Game/Asset/GameObject/Ground.png");
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground2").lock()->SetPosition(Vector3(700.0f, -350.0f, 0.0f));
	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground2").lock()->SetScale(Vector3(120.0f, 120.0f, 0.0f));

	// スライム
	objectmanager.AddObject<Enemy>(OBJECT, "Slime");
	objectmanager.GetGameObjectPtr<Enemy>(OBJECT, "Slime").lock()->Init(L"Game/Asset/GameObject/Slime.png");
	objectmanager.GetGameObjectPtr<Enemy>(OBJECT, "Slime").lock()->SetPosition(Vector3(200.0f, -300.0f, 0.0f));
	objectmanager.GetGameObjectPtr<Enemy>(OBJECT, "Slime").lock()->SetScale(Vector3(120.0f, 120.0f, 0.0f));

	// クロスヘア
	objectmanager.AddObject<CrossHair>(UI, "CrossHair");
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->Init(L"Game/Asset/UI/CrossHair.png");
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->SetPosition(Vector3(200.0f, 0.0f, 0.0f));
	objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair").lock()->SetScale(Vector3(30.0f, 30.0f, 0.0f));
	// クロスヘアをプレイヤーの子オブジェクトとして設定
	objectmanager.GetGameObject<Player>(PLAYER, "Player").second->SetChild(objectmanager.GetGameObject<CrossHair>(UI, "CrossHair").second);

	std::cout << "GameSceneInit" << std::endl;
	//// UI1(ボタン)
	//objectmanager.AddObject<GameObject>(UI, "StartButton");
	//// UI2(ボタン)
	//objectmanager.AddObject<GameObject>(UI, "ExitButton");
	//// プレイヤー
	//objectmanager.AddObject<Player>(PLAYER);
}



void TitleScene::Update(void)
{

	// 入力情報の更新
	Input::GetInstance().Update();

	// シーン更新に必要な情報を取得
	auto playerShared = objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player");
	auto groundShared = objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground");
	auto groundShared2 = objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Ground2");
	auto gionShared = objectmanager.GetGameObjectPtr<Poyon>(ONOMATOPOEIA, "Gion");
	auto enemyShared = objectmanager.GetGameObjectPtr<Enemy>(OBJECT, "Slime");
	auto crosshairShared = objectmanager.GetGameObjectPtr<CrossHair>(UI, "CrossHair");


	// 入力管理
	DirectX::XMFLOAT2 PlayerMove = Input::GetInstance().GetLeftAnalogStick();
	if (PlayerMove.x > 0.0f)
	{
		objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetMoveRight(true);

		//デバック用
		std::cout << "Playerの座標移動ができています" << std::endl;
	}
	if (PlayerMove.x < 0.0f)
	{
		objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetMoveLeft(true);

		//デバック用
		std::cout << "Playerの座標移動ができています" << std::endl;
	}

	// ジャンプ
	if (Input::GetInstance().GetButtonTrigger(XINPUT_GAMEPAD_A))
	{
		objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->SetJump(true);

		//デバック用
		std::cout << "Playerの座標移動ができています" << std::endl;
	}


	//ゲーム画面に遷移
	// シーン遷移（デバック用
	if (Input::GetInstance().GetKeyTrigger(VK_RETURN))
	{
		this->ChangeScene = true;
		SetChangeScene(this->ChangeScene);
	}


	//----------------当たり判定-----------------------

	ColliderPlayer_Ground(playerShared, groundShared);

	//! クロスヘアの入力取得(本来はプレイヤーのフラグを立てて、プレイヤーの更新の中でクロスヘアを動かすべき)
	//! 右スティックの座標を取って更新する
	DirectX::XMFLOAT2 crosshairSharedMove = Input::GetInstance().GetRightAnalogStick();
	if (crosshairSharedMove.x < 0.0f)
	{
		crosshairShared.lock()->SetMoveLeft(true);
		crosshairShared.lock()->SetMoveRight(false);
	}
	else if (crosshairSharedMove.x > 0.0f)
	{
		crosshairShared.lock()->SetMoveLeft(false);
		crosshairShared.lock()->SetMoveRight(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveLeft(false);
		crosshairShared.lock()->SetMoveRight(false);
	}

	if (crosshairSharedMove.y < 0.0f)
	{
		crosshairShared.lock()->SetMoveDown(true);
		crosshairShared.lock()->SetMoveUp(false);
	}
	else if (crosshairSharedMove.y > 0.0f)
	{
		crosshairShared.lock()->SetMoveDown(false);
		crosshairShared.lock()->SetMoveUp(true);
	}
	else
	{
		crosshairShared.lock()->SetMoveDown(false);
		crosshairShared.lock()->SetMoveUp(false);
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
	if (Input::GetInstance().IzZRPressed()==true)
	{
		// マガジンに擬音が装填されているかチェック
		if (playerShared.lock()->GetLoadedBullet())
		{
			Vector3 gion_Rot = gionShared.lock()->GetRotation();	// 擬音の回転情報
			Vector3 gion_Scale = gionShared.lock()->GetScale();		// 擬音のサイズ情報
			gion_Rot.z = 0;
			// 擬音のサイズ設定
			gion_Scale.y = 120;
			gion_Scale.x = 240;
			// 各情報を再設定
			gionShared.lock()->SetRotation(gion_Rot);
			gionShared.lock()->SetScale(gion_Scale);
			playerShared.lock()->SetIsShot(true);


			//--------------------------------------
			//			擬音のタグ変更処理
			//--------------------------------------

			// ここで擬音のタグをUIから擬音に変更
			// →擬音のポインタだけわかってるのにキーの特定がスムーズにできないのでやっぱり管理方法変えたほうがいい(登録されてるタグを毎フレーム確認して同期させるとか)

			// ここでは持ってきた擬音がキャストできた型によってその擬音のタグを変えるようにする
			auto bullet = playerShared.lock()->GetLoadedBullet();

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
		}
	}

	// 何かのオブジェクトに当たったら擬音の移動を止める処理
	if (Collider_toGround(groundShared2, gionShared))
	{
		playerShared.lock()->SetIsShot(false);

	}
	else {

	}


	//playerShared.lock()->Shot(gionShared);



	// ----------------吸い込み処理→ここはプレイヤーの処理に移す-------------------------
	// プレイヤー発の扇型と当たってる擬音を探す→(一番近くの)当たってる擬音を吸い込む
	if (Input::GetInstance().IzZLPressed() == true)
	{
		// 吸い込める擬音を探す
		// そのフレーム内のタグが擬音のもの全て取得→それとプレイヤーから出る扇型の当たり判定を取得
		auto onomatopoeias = objectmanager.GetObjects<IOnomatopoeia>(ONOMATOPOEIA);
		// 扇形との当たり判定を取得
		auto HitOnomatopoeia = ColliderFan_Gion(playerShared, onomatopoeias);

		// ポインタに値が入っていれば(扇形範囲内に当たった擬音があれば)
		if (HitOnomatopoeia.lock())
		{
			// 擬音の吸い込み実行
			playerShared.lock()->Suction(HitOnomatopoeia);
		}


		//Vector3 p_pos = objectmanager.GetGameObjectPtr<Player>(PLAYER, "Player").lock()->GetPosition();
		//Vector3 gion_pos = objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Gion").lock()->GetPosition();
		////Suction(gion_pos, p_pos);
		//if (gion_pos.x - p_pos.x <= 300 && gion_pos.x - p_pos.x >= 0)/*Playerと擬音の距離が一定に来たら、擬音が徐々に近づく*/
		//{
		//	//ここに、近づくスピードを書く
		//	gion_pos.x -= 14;
		//	std::cout << "吸い込んでます" << std::endl;
		//	objectmanager.GetGameObjectPtr<GameObject>(OBJECT, "Gion").lock()->SetPosition(gion_pos);
		//}
		//std::cout << "擬音座標：" << gion_pos.x << std::endl;
	}
	//連：メモ
	//擬音を回収したときに、オブジェクトをただ移動させるだけじゃなくて、回収したオブジェクトの情報によって表示させるUIを変える



	// ここでマガジンがUIになっていなければ当たり判定を取りたい
	if (m_MagCount >= 1)
	{
		// １つのシーンに落ちてるマガジン数は一個なので、シーンの持つマガジンカウントが１ならまだ当たっていない
		// →判定チェックする

		auto magShared = objectmanager.GetGameObject<Magazine>(OBJECT, "Magazine3");

		// マガジンと地面
		Collider_toGround(std::weak_ptr<Magazine>(magShared.second), groundShared);
		// プレイヤーとマガジンが当たったら
		if (Collider_Player_to_Magazine(playerShared, objectmanager.GetGameObjectPtr<Magazine>(OBJECT, "Magazine3")))
		{
			// マガジンのタグを変更
			objectmanager.ChangeTag(magShared.first.first, magShared.first.second, UI);
			// プレイヤーの子オブジェクトに設定
			playerShared.lock()->SetChild(magShared.second);
			/*magShared.second->SetScale(Vector3(75.0f, 75.0f, 0.0f));
			magShared.second->SetPosition(Vector3(-800.0f, -500.0f, 0.0f));*/
			m_MagCount = 0;
		}

	}

	// マガジンとの当たり判定を毎フレーム取る→マガジンを取得したらその判定チェックはしなくておｋ
	//objectmanager.Collider_Player_to_Object();		// ここで当たったらマガジン数を１つ減らす

	objectmanager.Update();

}

void TitleScene::Draw(void) {
	objectmanager.Draw();
}

void TitleScene::Uninit(void) {
	objectmanager.Uninit();
}
