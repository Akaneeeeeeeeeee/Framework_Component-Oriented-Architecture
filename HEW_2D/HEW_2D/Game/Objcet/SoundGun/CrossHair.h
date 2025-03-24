#pragma once
#include "../BaseObject/Object.h"
/**
 * @brief クロスヘアクラス
 * 
 * クロスヘア画像の移動だけ行う(クロスヘアはUI設定で登録されるので当たり判定を気にする必要はない)
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

