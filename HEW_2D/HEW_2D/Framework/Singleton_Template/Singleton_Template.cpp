#include "Singleton_Template.h"

template <class T>
T& Singleton<T>::GetInstance(void)
{
	// �ÓI�|�C���^�ϐ��Ƃ��ăV���O���g���̃C���X�^���X��ێ�����
	static T Instance;

	// �C���X�^���X��Ԃ�
	return Instance;
}

