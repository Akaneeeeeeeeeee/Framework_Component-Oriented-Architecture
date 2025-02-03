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
	std::weak_ptr<T> AddComponent(void)
	{
		//! コンポーネントのポインタを生成
		auto component = std::make_shared<T>();
		//! 取りつけたいコンポーネントが既に存在していれば
		if (m_Components.find(std::type_index(typeid(T))) != m_Components.end())
		{
			throw std::runtime_error("同一コンポーネントが既に存在しています");
		}
		//! なければコンポーネントに追加
		component->Init();
		m_Components.emplace(std::type_index(typeid(T)), component);
		//! コンポーネントのポインタを返す
		return std::weak_ptr<T>(component);
	}


	/**
	 * @brief コンポーネント取得関数
	 * @tparam T コンポーネントの型
	 * @return コンポーネントのポインタ
	*/
	template <class T>
	std::shared_ptr<T> GetComponent(void)
	{
		//! そのコンポーネントが存在しているかを探索
		for (auto& component : m_Components)
		{
			// そのコンポーネントの型にキャストできれば
			if (T* comp = dynamic_cast<T*>(component.second.get()))
			{
				//! コンポーネントのポインタを返す
				return std::shared_ptr<T>(component.second, comp);
			}
		}
		//! なければエラー出力
		std::cerr << typeid(T).name() << "を保持していません" << std::endl;
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