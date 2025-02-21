#pragma once
#include "../Component/IComponent/IComponent.h"

/**
 * @brief コンポーネント管理クラス
 *
 * コンポーネントどう管理する？→mapで管理する
 * 
 * 
 *
*/
class ComponentManager
{
public:
	ComponentManager(Object& _Owner) :m_Owner(_Owner) {

	}

	~ComponentManager() {
		Uninit();
	};

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

	void Init(void);
	//! Drawは描画機能を持つコンポーネントが担当するのでここには置かない
	void Update(void);
	void Uninit(void);

private:
	//! アタッチしているオブジェクトの参照→アタッチ先のオブジェクトは必ず存在していないといけないため参照を使う
	Object& m_Owner;
	//! コンポーネントの型とポインタをセットでmapに保持
	std::unordered_map<std::type_index, std::unique_ptr<IComponent>> m_Components;
};



