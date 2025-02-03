#pragma once
#include "../BaseObject/GameObject.h"

/**
 * @brief クロスヘアクラス
 * 
 * クロスヘア画像の移動だけ行う(クロスヘアはUI設定で登録されるので当たり判定を気にする必要はない)
*/
class CrossHair :public GameObject
{
public:
	CrossHair(D3D11& _D3d11):GameObject(_D3d11) {
		MoveLeft = false;
		MoveRight = false;
		MoveUp = false;
		MoveDown = false;
		m_Velocity = { 10.0f };	// クロスヘアの移動速度
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

