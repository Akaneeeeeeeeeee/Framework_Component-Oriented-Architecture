#pragma once
#include"../Character/Character.h"

class Enemy :public Character
{
public:
	Enemy(const UINT& _ID, const Tag& _tag, const std::string& _name) :Character(_ID, _tag, _name) {
		/*m_Velocity = { 0.0f };
		m_MoveSpeed = 1.0f;
		m_JumpPower = 7.0f;*/
	}
	~Enemy();//デストラクタ
	void Update();//エネミーの動作

};
