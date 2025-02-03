#pragma once
#include"../Character/Character.h"

class Enemy :public Character
{
public:
	Enemy(D3D11& _D3d11) :Character(_D3d11) {
		m_Velocity = { 0.0f };
		m_MoveSpeed = 1.0f;
		m_JumpPower = 7.0f;
	}
	~Enemy();//デストラクタ
	void Update();//エネミーの動作

};
