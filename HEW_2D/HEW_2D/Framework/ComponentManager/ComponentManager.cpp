#include "ComponentManager.h"
#include "../Component/Transform/TransformComponent.h"


/**
 * @brief 初期化
*/
void ComponentManager::Init(void)
{
	// Transformは必ず存在している
	auto pt = AddComponent<TransformComponent>();
	// オブジェクトをアタッチ
	pt.lock()->SetOwner(m_Owner);
	// コンポーネントの初期化
	for (auto& component : m_Components) {
		component.second->Init();
	}
}

/**
 * @brief 更新
*/
void ComponentManager::Update(void)
{
	for (auto& component : m_Components)
	{
		component.second->Update();
	}
}

/**
 * @brief 終了
*/
void ComponentManager::Uninit(void)
{
	for (auto& component : m_Components)
	{
		component.second->Uninit();
	}
}