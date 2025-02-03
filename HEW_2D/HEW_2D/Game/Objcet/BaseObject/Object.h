#pragma once
#include "../../../Framework/ComponentManager/ComponentManager.h"
#include "../../ObjectManager/ObjectManager.h"


/**
 * @brief ベースとなるオブジェクトクラス
 * 
 * 基本の2Dオブジェクトを描画するために必要なコンポーネント
 * ・SpriteRenderer
 * ・RigidBody2D
 * ・BoxCollider
 * ・
*/
class Object :public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();



	//-----------------------
	//-----テンプレート関数-----
	//-----------------------

	/**
	 * @brief コンポーネント追加関数
	 * @tparam T コンポーネント
	 * @return コンポーネントのweak_ptr→返した側でlock()関数を使わないとポインタを使えない
	*/
	template <class T>
	std::shared_ptr<T> AddComponent(void)
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


		// コンポーネントの型を取得
		std::type_index type = typeid(T);

		// 既に同じ型のコンポーネントが存在する場合、エラーを投げる
		if (m_Components.find(type) != m_Components.end()) {
			throw std::runtime_error("同一コンポーネントが既に存在しています");
		}

		// コンポーネントを生成し、所有する
		auto component = std::make_shared<T>(this);
		component->Init();

		// コンポーネントを登録
		m_Components.emplace(type, component);

		return component;
	}


	/**
	 * @brief コンポーネント取得関数
	 * @tparam T コンポーネントの型
	 * @return コンポーネントのポインタ
	*/
	template <class T>
	std::shared_ptr<T> GetComponent(void)
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





private:
	std::string m_Name;
	Tag m_Tag;
	
	// これいらなくね？ゲームオブジェクトの中のコンポーネントマネージャからじゃないとaddcomponentできない→オブジェクトがmapで管理しとくほうがいい
	//ComponentManager m_ComponentManager;

	// コンポーネントのmap
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> m_Components;

};

//Object::Object()
//{
//}
//
//Object::~Object()
//{
//}