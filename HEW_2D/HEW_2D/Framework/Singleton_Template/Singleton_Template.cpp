#include "Singleton_Template.h"

template <class T>
T& Singleton<T>::GetInstance(void)
{
	// �ÓI�ϐ��Ƃ��ăV���O���g���̃C���X�^���X��ێ�����
	static T Instance;

	// �C���X�^���X�̎Q�Ƃ�Ԃ�
	return Instance;
}

