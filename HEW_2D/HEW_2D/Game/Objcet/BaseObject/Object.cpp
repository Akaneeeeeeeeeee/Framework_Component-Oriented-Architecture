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
	// �`��n�R���|�[�l���g�������Ă���ꍇ�A�`�揈�����s��
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
