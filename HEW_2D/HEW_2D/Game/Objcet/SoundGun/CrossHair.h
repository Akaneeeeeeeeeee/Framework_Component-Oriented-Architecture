#pragma once
#include "../BaseObject/Object.h"
/**
 * @brief �N���X�w�A�N���X
 * 
 * �N���X�w�A�摜�̈ړ������s��(�N���X�w�A��UI�ݒ�œo�^�����̂œ����蔻����C�ɂ���K�v�͂Ȃ�)
*/
class CrossHair :public Object
{
public:
	CrossHair(const UINT& _ID, const Tag& _tag, const std::string& _name);

	~CrossHair() {};
	void Update(void);
	void SetMoveLeft(bool _flg) { MoveLeft = _flg; }
	void SetMoveRight(bool _flg) { MoveRight = _flg; }
	void SetMoveUp(bool _flg) { MoveUp = _flg; }
	void SetMoveDown(bool _flg) { MoveDown = _flg; }

private:
	bool MoveLeft;
	bool MoveRight;
	bool MoveUp;
	bool MoveDown;
};

