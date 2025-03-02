#include "Character.h"

Character::Character(const UINT& _ID, const Tag& _tag, const std::string& _name) :Object(_ID, _tag, _name) {
	MoveUp = false;
	MoveDown = false;
	MoveLeft = false;
	MoveRight = false;
	Jump = false;
	Jumping = false;
	//OnGround = false;
	m_JumpPower = 0.0f;
	m_MoveSpeed = 0.0f;
}


//-------------------------------------------
//			�ړ��֘A�̃t���O�̃Q�b�^�[
//-------------------------------------------
bool Character::GetMoveUp(void) {
	return MoveUp;
}

bool Character::GetMoveDown(void) {
	return MoveDown;
}

bool Character::GetMoveLeft(void) {
	return MoveLeft;
}

bool Character::GetMoveRight(void) {
	return MoveRight;
}

bool Character::GetJump(void) {
	return Jump;
}


//-------------------------------------------
//			�ړ��֘A�̃t���O�̃Z�b�^�[
//-------------------------------------------
void Character::SetMoveUp(bool _flg) {
	MoveUp = _flg;
}

void Character::SetMoveDown(bool _flg) {
	MoveDown = _flg;
}

void Character::SetMoveLeft(bool _flg) {
	MoveLeft = _flg;
}

void Character::SetMoveRight(bool _flg) {
	MoveRight = _flg;
}

void Character::SetJump(bool _flg) {
	Jump = _flg;
}

void Character::Update(void)
{

}

