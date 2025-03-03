#pragma once
#include "../BaseObject/Object.h"

/**
 * @brief �J�����N���X
 * 
 * ���K�v�Ȃ��́�
 * �@�E�`�悵������ʂ̑傫��(���A����)
 * �@�E�J�����̍��W(�����_�̓Q�[���I�ɕK�v�Ȃ�����)
 * �@�E�`��@�\
 * 
 * �E���Ԃ��Ȃ��̂ō���̃J�����͍��̉摜�����������ʂ̃I�u�W�F�N�g�Ƃ���
 * 
 * ����ȂƂ��납�H�����蔻�������Ȃ���
 * ���ŁA�J������ʓ��ɂ��郂�m�����`�悷��A�Ƃ���΍s����͂�
*/
class Camera : public Object
{
public:
	Camera();

	~Camera() {};
	
	void Update(void);		//! �J�����X�s�[�h�ƃI�u�W�F�N�g�̈ʒu
	void SetIsMoving(bool _flg) { IsMoving = _flg; }

private:
	bool OnFade;	// �t�F�[�h��
	bool FadeIn;	// �t�F�[�h�C��/�A�E�g����
	bool IsMoving;	// �ړ���������
};
