#pragma once
#include "../../../Game/EntryPoint/main.h"

/// <summary>
/// �S�ẴR���|�[�l���g�̌��ƂȂ�N���X
/// �R���|�[�l���g�͂�����A�^�b�`�i�����j����I�u�W�F�N�g������̂Ń����o�ϐ��Ƃ���GameObjcet�N���X�̃|�C���^������
/// ������ɂ���ăR���|�[�l���g����A�^�b�`���Ă���I�u�W�F�N�g�ɃA�N�Z�X���邱�Ƃ��ł���
/// </summary>

class GameObject;

class IComponent
{
public:
	IComponent(GameObject* _Owner) :m_pOwner(_Owner) {};
	virtual ~IComponent() { m_pOwner = nullptr; }

	virtual void Init(void) = 0;		// ������
	virtual void Update(void) = 0;		// �X�V
	virtual void Uninit(void) = 0;		// �I��

	void SetOwner(const GameObject& _obj);		// �I�u�W�F�N�g�̃A�^�b�`(�Q�Ɠn��)
	GameObject* GetOwner(void);					// �A�^�b�`��̃I�u�W�F�N�g�̎擾
	//void RemoveOwner(void);			// �A�^�b�`����Ă���I�u�W�F�N�g����̎��O��

protected:
	// �R���|�[�l���g�}�l�[�W����shared_ptr�ŊǗ����Ă�̂ŁA�����ŎQ�Ƃ��g���ƃI�u�W�F�N�g���������ꍇ�Q�Ƃ������Ă��܂��̂�NG���|�C���^�ŊǗ�
	// �Q�Ɓ�null���g���Ȃ����I�u�W�F�N�g�̕�����ɍ폜���ꂽ�ꍇ�A����`����ɂȂ邩���Ȃ̂Ł~
	// unique,shared���R���|�[�l���g���I�u�W�F�N�g�̎�L�������K�v���Ȃ��̂Ł~
	// ���|�C���^�ɂ���
	GameObject* m_pOwner;				// �A�^�b�`����Ă���I�u�W�F�N�g�̃|�C���^(�P��Ȃ̂�unique_ptr�H)
};



