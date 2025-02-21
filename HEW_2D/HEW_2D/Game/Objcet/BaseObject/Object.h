#pragma once
#include "../../../Framework/ComponentManager/ComponentManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../../Framework/Component/Transform/TransformComponent.h"


/**
 * @brief ベースとなるオブジェクトクラス
 * 
 * 基本の2Dオブジェクトを描画するために必要なコンポーネント
 * ・SpriteRenderer
 * ・RigidBody2D
 * ・BoxCollider
 * ・
 * 
 * コンポーネントマネージャを作ることも考えたが、そこへのアクセスする分時間もったいないのでは→オブジェクトが直で持つようにする(必要があれば後から変更)
*/
class Object :public std::enable_shared_from_this<Object>
{
public:
	Object() {
		// コンストラクタでTransformコンポーネントだけ自動で追加しておく
		AddComponent<TransformComponent>(this);
	};

	Object(const Tag& _tag, const std::string& _name) :m_Tag(_tag), m_Name(_name) {
		// コンストラクタでTransformコンポーネントだけ自動で追加しておく
		AddComponent<TransformComponent>(this);
	};


	virtual ~Object() {};

	//-----------------------
	//-----テンプレート関数-----
	//-----------------------

	/**
	 * @brief コンポーネント追加関数
	 * @tparam T コンポーネント
	 * @return コンポーネントのweak_ptr→返した側でlock()関数を使わないとポインタを使えない
	*/
	template <class T>
	T* AddComponent(Object* _Owner)
	{
		////! コンポーネントのポインタを生成
		//auto component = std::make_shared<T>();
		////! 取りつけたいコンポーネントが既に存在していれば
		//if (m_Components.find(std::type_index(typeid(T))) != m_Components.end())
		//{
		//	throw std::runtime_error("同一コンポーネントが既に存在しています");
		//}
		////! なければコンポーネントに追加
		//component->Init();
		//m_Components.emplace(std::type_index(typeid(T)), component);
		////! コンポーネントのポインタを返す
		//return std::weak_ptr<T>(component);

		// コンパイル時チェック
		static_assert(std::is_base_of<IComponent, T>::value, "T は Component を継承している必要があります");
		static_assert(std::is_constructible<T, Object*>::value, "T は Object* を受け取るコンストラクタを持つ必要があります");

		// コンポーネントの型を取得
		std::type_index type = typeid(T);

		// 既に同じ型のコンポーネントが存在する場合、エラーを投げる
		if (m_Components.find(type) != m_Components.end()) {
			throw std::runtime_error("同一コンポーネントが既に存在しています");
		}

		// コンポーネントを生成し、所有する
		auto component = std::make_unique<T>(_Owner);
		component->Init();

		// コンポーネントを登録
		m_Components.emplace(type, std::move(component));

		return component.get();
	}


	/**
	 * @brief コンポーネント取得関数
	 * @tparam T コンポーネントの型
	 * @return コンポーネントの生ポインタ
	*/
	template <class T>
	T* GetComponent(void)
	{

		// コンポーネントの型を取得
		std::type_index type = typeid(T);

		//! そのコンポーネントが存在しているかを探索
		auto it = m_Components.find(type);
		if (it != m_Components.end())
		{
			// 目的の型にキャストして返す
			return std::dynamic_pointer_cast<T>(it->second);
		}

		// なければエラー出力
		std::cerr << typeid(T).name() << " を保持していません" << std::endl;
		return nullptr;  // コンポーネントが見つからなければ nullptr を返す
	}

	/**
	 * @brief "全"コンポーネントを取得する関数
	 * @tparam T 
	 * @param  
	 * @return 
	 * 
	 * →この機能使う場面が想像できないので作るの一旦止めとく。必要になったら作る！
	*/
	/*template <class T>
	std::vector<IComponent> GetComponents(void)
	{

	}*/


	//----------------------------
	//			基本関数
	//----------------------------
	virtual void Init() = 0;
	virtual void Update(void) = 0;
	// 描画は更新処理内で行う？関数だけ作っておいて、描画コンポーネントがある場合に処理を行う？
	virtual void Uninit(void) = 0;


protected:
	std::string m_Name = "GameObject";
	Tag m_Tag = Tag::NONE;
	
	// これいらなくね？ゲームオブジェクトの中のコンポーネントマネージャからじゃないとaddcomponentできない→オブジェクトがmapで管理しとくほうがいい
	//ComponentManager m_ComponentManager;

	// コンポーネントのmap(所有権が怖いのでuniqueで管理)
	std::unordered_map<std::type_index, std::unique_ptr<IComponent>> m_Components;

};
