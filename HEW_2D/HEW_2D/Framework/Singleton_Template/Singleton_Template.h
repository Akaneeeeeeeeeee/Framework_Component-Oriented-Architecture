#pragma once


/**
 * @brief �e���v���[�g�������V���O���g���N���X
 * @tparam T �V���O���g���ɂ������N���X�̌^
 * 
 * ���̃N���X���p�����邱�ƂŔh���N���X���S�ăV���O���g���̂���ɂȂ�
*/
template <class T>
class Singleton
{
public:
	// �C���X�^���X�擾�֐�
	static T& GetInstance(void);

protected:
	// �O������̃C���X�^���X�����ƍ폜�������Ȃ�
	Singleton() {};
	~Singleton() {};

private:
	Singleton(const Singleton&) = delete;				// �R�s�[�R���X�g���N�^���폜
	Singleton& operator=(const Singleton&) = delete;	// ������Z�q���폜
};

