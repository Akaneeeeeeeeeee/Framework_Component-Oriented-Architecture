#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../../Framework/Sound/sound.h"
#include "../../Framework/Graphics/Graphics.h"


/**
 * @brief �^�C�g���V�[���N���X
 * 
 * �T�E���h�A�w�i�Ȃǂ̃Q�[���I�u�W�F�N�g��z��iarray�j�Ŏ���
 * 
 * �I�u�W�F�N�g���R���X�g���N�^�ő�����Ă����A�V�[���̏������������ŃI�u�W�F�N�g������������
*/
class Stage1Scene :public IScene
{
public:
	Stage1Scene() :IScene() {
		// �I�u�W�F�N�g�̒ǉ��̓V�[���̏������ōs��
		// �T�E���h�Ƃ����̃V�[���̂ݑ��݂�����̂�����΂��̏��������s��
		ChangeScene = false;
		CurrentFrame = FRAME1;	// ���݃t���[�����t���[��1��
		OldFrame = FRAME_MAX;	// ��t���[���O�͂Ȃ�
	};
	~Stage1Scene() {};
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;

	void Frame2Init(void);
	void Frame3Init(void);
	void Frame4Init(void);


private:
	FRAME CurrentFrame;		// ���݂̃t���[��
	FRAME OldFrame;			// ��t���[���O�̃t���[��

};



// 289�`317 �X���C������
// 539�`612 �[������