#include "Character.h"

//-------------------------------------------
//			移動関連のフラグのゲッター
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
//			移動関連のフラグのセッター
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

