#include "ObjectManager.h"
#include "../../Framework/Component/Collider/BoxCollider2D/Collider.h"


/**
 * @brief オブジェクト削除関数
 * @param object 
*/
void ObjectManager::DeleteObject(Tag _ObjName) {
	//! オブジェクト配列が空でなければ
	if (!this->Objects.empty()) {
		//! 指定した要素を削除
		//Objects.(_ObjName);
	}
}


/**
 * @brief プレイヤーと何かの当たり判定
 * 
 * 
*/
void ObjectManager::Collider_Player_to_Object(void)
{
	// プレイヤー取得
	auto playerobj = GetGameObjectPtr<Player>(PLAYER, "Player");
	
	// 変更予定のオブジェクトを記録するリスト
	std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<GameObject>>> toBeUpdated;


	// プレイヤーと当たったオブジェクトを確認
	for (auto& obj : Objects) {
		// タグが地面、オブジェクト、敵のものだけ当たり判定を取る
		switch (obj.first.first)
		{
		// オブジェクトが地面なら
		case BACKGROUND:
			// 地面との当たり判定を取る
			Collider_toGround(playerobj, obj.second);
			break;
		// 画像は当たり判定を取らない
		case IMAGE:
			break;
		// UIも判定を取らない
		case UI:
			break;
		// ゲームオブジェクトなら判定を取る
		case OBJECT:
			// ここはマガジンの判定を取っている
			if (Collider_to_Object(playerobj, obj.second))
			{
				toBeUpdated.push_back(obj); // 変更対象を記録
			}
			break;
		case GROUND:
			break;
		case PLAYER:
			break;
		case ENEMY:
			break;
		default:
			break;
		}
		
	}

	// 記録した変更対象を処理(マガジン用だが、中身を変えればオブジェクトの削除も可能)
	for (auto& it : toBeUpdated) {
		auto mag = std::dynamic_pointer_cast<Magazine>(it.second);
		if (mag) {
			// マガジンのタグを変更
			ChangeTag(it.first.first, it.first.second, UI);
			// プレイヤーの子オブジェクトに設定
			playerobj.lock()->SetChild(mag);
			mag->SetScale(Vector3(50.0f, 50.0f, 0.0f));
			mag->SetPosition(Vector3(-800.0f, -500.0f, 0.0f));
		}
	}
}


/**
 * @brief タグ変更関数
 * @param _oldtag 変更前のタグ
 * @param _name タグを変更したいオブジェクト名
 * @param _newTag 変更後のタグ
 * @return 結果
*/
bool ObjectManager::ChangeTag(Tag _oldtag, const std::string _name, Tag _newTag)
{
	// 現在のキーを作成
	auto oldKey = std::make_pair(_oldtag, _name);

	// 1. 元のキーでオブジェクトを検索
	auto it = Objects.find(oldKey);
	if (it == Objects.end()) {
		std::cerr << "オブジェクトが見つかりません: " << _name << std::endl;
		return false;
	}

	// 2. オブジェクトを取得し、マップから削除
	auto obj = it->second;
	Objects.erase(it);

	// 3. 新しいタグで再登録
	auto newKey = std::make_pair(_newTag, _name);
	Objects[newKey] = obj;

	return true;
}



/**
 * @brief オブジェクト初期化
 * コンストラクタでオブジェクトを一括追加→Init内で初期化が良さげ？→それぞれ初期化値が違うのでここでオブジェクトのInitを回せない
 * 
 * ここではコンテナの初期化だけを行う
*/
void ObjectManager::Init(void) {
	// オブジェクト管理用コンテナの初期化
	Objects.clear();
}

void ObjectManager::Update(void) {

	// 範囲for文
	for (auto& obj : Objects)
	{
		obj.second->Update();
	}
	
}


/**
 * @brief 描画
 * 
 * カメラがある場合は、そのオブジェクトの大きさ以内にいるものだけを描画する
 * カメラがない場合はそのまま描画
*/
void ObjectManager::Draw(void) {
	D3d11.StartRender();


	// カメラがある場合
	if (auto cam = HasCamera())
	{
		// 描画するべきオブジェクトを格納していく
		std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<GameObject>>> drewobj;
		
		// カメラの描画範囲
		float left = cam->GetPosition().x - cam->GetScale().x / 2;  // カメラの左端
		float right = cam->GetPosition().x + cam->GetScale().x / 2; // カメラの右端
		float up = cam->GetPosition().y + cam->GetScale().y / 2;    // カメラの上端
		float down = cam->GetPosition().y - cam->GetScale().y / 2;  // カメラの下端

		// オブジェクトをチェック
		for (auto& obj : Objects) {
			float objX = obj.second->GetPosition().x;
			float objY = obj.second->GetPosition().y;

			// オブジェクトのx座標がカメラの視界範囲内、かつy座標が視界範囲内にある場合
			if (left <= objX && objX <= right && down <= objY && objY <= up) {
				// オブジェクトを描画するべきリストに追加
				drewobj.push_back(obj);  // 必要に応じて追加処理
				obj.second->Draw();      // オブジェクトを描画
			}
		}

		// 範囲for文
		// 先に背景から描画
		for (auto& obj : drewobj)
		{
			if (obj.first.first == BACKGROUND)
			{
				// firstがキー（ObjectName）,secondがオブジェクト本体
				obj.second->Draw();
			}
		}

		// 背景とUI以外を描画
		for (auto& obj : drewobj)
		{
			if (obj.first.first != BACKGROUND && obj.first.first != UI)
			{
				obj.second->Draw();
			}
		}

		// 最後にUIを描画
		for (auto& obj : drewobj)
		{
			if (obj.first.first == UI)
			{
				obj.second->Draw();
			}
		}
		
	}
	// カメラがない場合
	else
	{
		// 範囲for文
		// 先に背景から描画
		for (auto& obj : Objects)
		{
			if (obj.first.first == BACKGROUND)
			{
				// firstがキー（ObjectName）,secondがオブジェクト本体
				obj.second->Draw();
			}
		}

		// 背景とUI以外を描画
		for (auto& obj : Objects)
		{
			if (obj.first.first != BACKGROUND && obj.first.first != UI)
			{
				obj.second->Draw();
			}
		}

		// 最後にUIを描画
		for (auto& obj : Objects)
		{
			if (obj.first.first == UI)
			{
				obj.second->Draw();
			}
		}
	}

	D3d11.FinishRender();
}

void ObjectManager::Uninit(void) {
	// 範囲for文
	for (auto& obj : Objects)
	{
		// firstがキー（ObjectName）,secondがオブジェクト本体
		// オブジェクトの中身を解放
		obj.second->Uninit();
	}
	// コンテナ全体を解放
	Objects.clear();
}


/**
 * @brief 全てのオブジェクトを取得
 * @return 
*/
std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<GameObject>>> ObjectManager::GetAllObjects(void)
{
	std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<GameObject>>> ret;
	for (auto& obj : Objects)
	{
		ret.emplace_back(obj);
	}
	return ret;
}


/**
 * @brief カメラがあればそのポインタを返す
 * @param  
 * @return 
*/
std::shared_ptr<Camera> ObjectManager::HasCamera(void)
{
	for (const auto& obj : Objects) {
		if (auto casted = std::dynamic_pointer_cast<Camera>(obj.second)) {
			return casted;  // 1つ見つかったら終了
		}
	}
}
