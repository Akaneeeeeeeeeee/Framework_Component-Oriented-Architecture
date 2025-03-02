#pragma once
#include "../BaseObject/Object.h"

/**
 * @brief 全キャラクターの元となるクラス
 * シーン側では入力の取得、フラグ立てだけを行い、このクラスの派生クラスで個々の動きを書く
*/
class Character :public Object
{
public:
	Character(const UINT& _ID, const Tag& _tag, const std::string& _name);

	virtual ~Character() {};

	virtual void Update(void);

	// ゲッターセッター系
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
	// 上下左右の移動フラグ(ステートでもいい説)
	bool MoveUp;		// (今ないけど)上移動中か？
	bool MoveDown;		// (今ないけど)下移動中か？
	bool MoveLeft;		// 左移動中か？
	bool MoveRight;		// 右移動中か？
	bool Jump;			// ジャンプしたか？
	bool Jumping;		// ジャンプ中か？

	float m_JumpPower;		// ジャンプ力
	float m_MoveSpeed;		// 移動速度
};

