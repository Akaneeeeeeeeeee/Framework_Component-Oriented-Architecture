#include "../../../Game/EntryPoint/main.h"
#include "IComponent.h"


// ���̃R���|�[�l���g�����I�u�W�F�N�g�̊��蓖��(�����F�I�u�W�F�N�g(�Q��))
void IComponent::SetOwner(const GameObject& _obj) {
	// �Q�Ƃ����I�u�W�F�N�g�̃A�h���X��&�ő��
	m_pOwner = &_obj;
}

// �A�^�b�`��̃I�u�W�F�N�g�̎擾
GameObject* IComponent::GetOwner(void) {
	return m_pOwner;
}

