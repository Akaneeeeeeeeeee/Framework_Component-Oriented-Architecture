#pragma once
#include "../BaseObject/Object.h"

/**
 * @brief �S�L�����N�^�[�̌��ƂȂ�N���X
 * �V�[�����ł͓��͂̎擾�A�t���O���Ă������s���A���̃N���X�̔h���N���X�ŌX�̓���������
*/
class Character :public Object
{
public:
	Character(const UINT& _ID, const Tag& _tag, const std::string& _name);

	virtual ~Character() {};

	virtual void Update(void);

	// �Q�b�^�[�Z�b�^�[�n
	virtual bool GetMoveUp(void);
	virtual bool GetMoveDown(void);
	virtual bool GetMoveLeft(void);
	virtual bool GetMoveRight(void);
	virtual bool GetJump(void);

	virtual void SetMoveUp(bool _flg);
	virtual void SetMoveDown(bool _flg);
	virtual void SetMoveLeft(bool _flg);
	virtual void SetMoveRight(bool _flg);
	virtual void SetJump(bool _flg);


protected:
	// �㉺���E�̈ړ��t���O(�X�e�[�g�ł�������)
	bool MoveUp;		// (���Ȃ�����)��ړ������H
	bool MoveDown;		// (���Ȃ�����)���ړ������H
	bool MoveLeft;		// ���ړ������H
	bool MoveRight;		// �E�ړ������H
	bool Jump;			// �W�����v�������H
	bool Jumping;		// �W�����v�����H

	float m_JumpPower;		// �W�����v��
	float m_MoveSpeed;		// �ړ����x
};

