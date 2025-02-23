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
	CrossHair():Object() {
		MoveLeft = false;
		MoveRight = false;
		MoveUp = false;
		MoveDown = false;
		GetComponent<RigidBody2D>()->AddForce(Vector3(10.0f, 0.0f, 0.0f), ForceMode2D::VelocityChange);	// クロスヘアの移動速度
	}

	~CrossHair() {};
	void Update(void) override;
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

