#include "Object.h"
#include "../../../Framework/Component/Renderer/IRenderer/IRenderer.h"


void Object::Init(void)
{

}


void Object::Update(void)
{

}


void Object::Draw(void)
{
	// 描画系コンポーネントを持っている場合、描画処理を行う
	for (auto& component : m_Components)
	{
		if (auto rendercomponent = dynamic_cast<IRenderer*>(component.second.get()))
		{
			rendercomponent->Render();
		}
	}
}

void Object::Uninit(void)
{
	m_Components.clear()
}
