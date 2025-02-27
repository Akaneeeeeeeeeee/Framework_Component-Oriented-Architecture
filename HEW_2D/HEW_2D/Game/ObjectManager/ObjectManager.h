#pragma once
#include "../EntryPoint/main.h"
#include "../Objcet/Player/Player.h"
#include "../Objcet/SoundGun/SoundGun.h"
#include "../Objcet/Camera/Camera.h"

//TODO: いちいちダウンキャストするのめんどくさいから関数にしちゃって、指定した型にダウンキャストしたポインタを返す関数作ったほうがいい

/**
 * @brief オブジェクトのmapを管理するために使うstd::pairの二つmapに紐づける関数
*/
struct PairHash {
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& pair) const {
		auto hash1 = std::hash<T1>{}(pair.first);  // first のハッシュ値
		auto hash2 = std::hash<T2>{}(pair.second); // second のハッシュ値
		return hash1 ^ (hash2 << 1);               // ハッシュ値を組み合わせる
	}
};

/**
 * @brief オブジェクトを管理するクラス
*/
class ObjectManager
{
public:
	ObjectManager() = default;
	/*ObjectManager(D3D11& _D3d11) :D3d11(_D3d11) {

	}*/
	~ObjectManager() {};

	/**
	 * @brief オブジェクト個別追加関数
	 * @tparam T オブジェクトの型
	 * 
	 * ID設定、タグ設定、名前設定を行ってコンテナに追加
	*/
	template <typename T>
	void AddObject(const Tag& _Tag, const std::string _Name)
	{
		// ID(完全一意のものを設定)
		static UINT id = 0;
		// コンパイル時チェック
		static_assert(std::is_base_of<T, Object>, "このオブジェクトはObjectを継承していません");
		// オブジェクト生成
		auto obj = std::make_unique<T>(++id, _Tag, _Name);
		// コンテナに追加
		Objects.push_back(std::move(obj));
	}


	/**
	 * @brief 指定したタグのオブジェクトをvectorで渡して追加する関数
	*/
	//template <typename T>
	//void AddObject(Tag _Tag, std::vector<std::unique_ptr<T>> _Objects)
	//{
	//	// 引数の長さ分オブジェクト追加関数を回す
	//	for (auto& object : _Objects)
	//	{
	//		AddObject(_Tag, std::move(object));
	//	}
	//}

	/**
	 * @brief オブジェクト複数追加関数
	 * @tparam T 生成するオブジェクトの型
	 * @tparam ...Keys 受け取るキーの型（std::pair<Tag, std::string>を想定）
	 * @param ...keys 実際に受け取る引数
	*/
	template <typename T, typename ...Keys>
	void AddObjects(Keys&&... keys)
	{
		(AddObject<T>(std::forward<Keys>(keys).first, std::forward<Keys>(keys).second), ...);
	}


	/**
	 * @brief オブジェクト取得関数
	 * @tparam T オブジェクトの型
	 * @param _tag タグ
	 * @param _name 名前
	 * @return mapに登録されている状態(タグと名前がセットになった状態)でのオブジェクト
	*/
	//template <class T>
	//std::pair<const std::pair<Tag, std::string>, std::shared_ptr<T>> GetGameObject(const Tag& _tag, const std::string& _name)
	//{
	//	// 名前とタグを持つオブジェクトを探索
	//	//std::pair<std::pair<Tag, std::string>, std::shared_ptr<T>> retobj;
	//	for (auto& obj : Objects)
	//	{
	//		// 名前とタグが一致すれば
	//		if (obj.first.first == _tag && obj.first.second == _name)
	//		{
	//			// ダウンキャストを試みる
	//			auto castedObj = std::dynamic_pointer_cast<T>(obj.second);
	//			if (castedObj)
	//			{
	//				// キャスト成功時、適切に返す
	//				return std::make_pair(obj.first, castedObj);
	//			}
	//			else
	//			{
	//				// キャスト失敗時の処理（例外を投げる、もしくはエラーハンドリング）
	//				throw std::runtime_error("指定したオブジェクトの型にキャストできませんでした");
	//			}
	//		}
	//	}
	//	// 一致するオブジェクトが見つからない場合
	//	throw std::runtime_error("指定されたタグと名前のオブジェクトが見つかりませんでした");
	//}


	/**
	 * @brief	オブジェクトを配列で取得する関数
	 * @tparam T オブジェクトの型
	 * @param  オブジェクトのタグ
	 * @return タグで指定したオブジェクトをマネージャに登録した状態でvectorにしたもの
	*/
	//template <class T>
	//std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<T>>> GetGameObjectPair(const Tag& _tag)
	//{
	//	std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<T>>> returnobjects;
	//	// map内を探索
	//	for (auto& obj : Objects)
	//	{
	//		// タグが同じで
	//		if (obj.first.first == _tag)
	//		{
	//			// キャストできるならキャストして配列に格納
	//			if (auto casted = std::dynamic_pointer_cast<T>(obj.second))
	//			{
	//				returnobjects.emplace_back(obj.first, casted);
	//			}
	//			// 基底クラスならそのまま格納
	//			else
	//			{
	//				returnobjects.emplace_back(obj.first, std::static_pointer_cast<T>(obj.second));
	//			}
	//		}
	//	}
	//	return returnobjects;
	//}


	/**
	 * @brief オブジェクト取得関数(タグ、型指定してオブジェクトそのもののweak_ptrを返す)
	 * @tparam T オブジェクトの型
	 * @param _tag オブジェクトタグ
	 * @return 指定した型・タグと同一の情報を持つオブジェクトの配列
	 * 
	 * 2025/01/22 赤根：名前振るように作ったけどその仕組みまだ作れてないから使わないかも！！
	*/
	template <class T>
	std::vector<std::shared_ptr<T>> GetObjects(Tag _tag)
	{
		// オブジェクト保存用コンテナ
		std::vector<std::shared_ptr<T>> objects;
		for (auto& obj : Objects)
		{
			// タグが同じかを調べ、
			if (obj.first.first == _tag)
			{
				auto casted = std::dynamic_pointer_cast<T>(obj.second);
				// dynamic_pointer_castで型チェックし、型が同じであれば配列に追加
				if (casted) {
					objects.push_back(casted);
				}
			}
		}
		return objects;
	}


	/**
	 * @brief オブジェクト削除関数
	 * @param object 削除対象オブジェクト
	*/
	void DeleteObject(Tag _ObjTag);

	// オブジェクト取得関数
	//GameObject* GetGameObject(const Tag& _Tag, const std::string _Name);

	/**
	 * @brief オブジェクト取得関数(weak_ptrを返す)
	 * @param _Tag オブジェクトタグ
	 * @param _Name 付けた
	 * @return オブジェクトの生ポインタ(タグの型にキャストしてから返す)
	*/
	template <class T>
	T* GetGameObject(const std::string& _Name)
	{
		// タグと名前の一致するオブジェクトを見つける(見つからない場合はend()が返ってくる)
		for (auto& iterator : Objects) {
			// 見つかった場合、一番最初に見つかった同条件のオブジェクトのポインタを返す
			if (iterator.get()->GetName() == _Name)
			{
				// ポインタを取得して型に合わせて一度shared_ptrにキャスト
				static_assert(std::is_base_of<T, Object>::value, "TはObjectを継承している必要があります");
				auto castedptr = dynamic_cast<T*>(iterator.get());

				// キャストが成功した場合(nullptrではない場合)
				if (castedptr)
				{
					// ポインタを返す(ここで自動的にweak_ptrに変換される)
					return castedptr;
				}
			}
		}
		// 見つからなければ空のweak_ptrを返す
		return nullptr;
	}

	// 全オブジェクトを取得する
	//std::vector<std::pair<std::pair<Tag, std::string>, std::shared_ptr<Object>>> GetAllObjects(void);

	// カメラがあればそのポインタを返す関数
	//std::shared_ptr<Camera> HasCamera(void);

	/**
	 * @brief タグ変更関数
	 * @param _tag 
	 * @param _name 
	 * @param _newTag 
	 * @return 
	*/
	bool ChangeTag(Tag _tag, const std::string _name, Tag _newTag);

	// 当たり判定確認&場合分けした処理を行う関数
	void Collider_Player_to_Object(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

	// 当たり判定も追加予定

private:
	//TODO:1216ここまで！オブジェクト管理にmapを使う&オブジェクト生成関数で一度で複数のオブジェクトを呼び出せるように変更する！！
	//! オブジェクトのユニークポインタをmapで持つ→オブジェクトマネージャーがオブジェクトを管理する
	//! 
	//! (もしかしたら左にあるオブジェクトから順に配列に保持してもいいかも？→その場合もう一度設計が必要)
	//! 
	//! オブジェクトの管理はタグ（大まかな分類）と名前（一意のもの）を使う

	// unordered_mapにpairを使う場合、pairの紐づけないといけないためPairHashをmapの引数に入れる
	//std::unordered_map<std::pair<Tag, std::string>, std::shared_ptr<GameObject>, PairHash> Objects;
	//std::vector<std::shared_ptr<GameObject>> m_DrawObjects;		// 描画するオブジェクトを保存するコンテナ(毎フレームこの中のオブジェクトだけを描画する)
	//D3D11& D3d11;
	std::vector<std::unique_ptr<Object>> Objects;		// 完全一意の検索手段がないのでvectorにしてしまう
};
