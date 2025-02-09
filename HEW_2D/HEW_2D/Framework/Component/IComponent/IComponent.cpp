#include "../../../Game/EntryPoint/main.h"
#include "IComponent.h"


// そのコンポーネントを持つオブジェクトの割り当て(引数：オブジェクト(参照))
void IComponent::SetOwner(const GameObject& _obj) {
	// 参照したオブジェクトのアドレスを&で代入
	m_pOwner = &_obj;
}

// アタッチ先のオブジェクトの取得
GameObject* IComponent::GetOwner(void) {
	return m_pOwner;
}

