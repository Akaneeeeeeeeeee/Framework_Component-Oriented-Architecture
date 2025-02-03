#include"Enemy.h"

void Enemy::Update()
{
	m_Direction = { 0.0f };
	Vector3 enemy_pos = transform.GetPosition();

	// 方向ベクトルを合成
	// ジャンプした場合
	
		// ジャンプ中でなければ
		// ジャンプ処理
	if (Jump && !Jumping)
	{

		Jumping = true;					// ジャンプ中に設定(これステートでもいいかも)
		m_Velocity.y += m_JumpPower;	// 速度のY成分にジャンプ力を代入
		m_Direction.y += 1.0f;			// 上向きの方向ベクトルを加算
		Jump = false;                   //ジャンプフラグはfalse

	}
		
	

	// 下降している場合(ジャンプ中でベクトルのY成分が負(-)の時)
	if (Jumping && m_Velocity.y < 0.0f)
	{
		//Animation(JUMP);
		// 地面に足がついた場合は方向ベクトルをリセット
		if (OnGround)
		{
			// 着地フラグを立てて
			Jumping = false;
			// 通常時アニメーションへ変更
			//Animation(RUN);
		}
		else
		{
			// そうでない場合(下降中の場合)
			m_Direction.y -= 1.0f;	// 下向きの方向ベクトルを加算
		}
	}
	

	// 左移動しようとしている場合
	m_Direction.x -= 1.0f;	// 左向きの方向ベクトルを加算

	// 正規化(長さを１に揃える)
	if (m_Direction.Length() > 0.0f)
	{
		m_Direction.Normalize();
	}
	else
	{
		m_Direction = { 0.0f, 0.0f, 0.0f };  // 明示的に方向ベクトルをリセット
	}

	// 地面の上にいない場合、重力分速度を減算
	if (!OnGround)
	{
		Jumping = true;
		m_Velocity.y -= 0.2f;	// 重力加速度実装の場合ここを変更
	}
	else {
		// 接地していればジャンプ中ではない
		Jumping = false;
	}

	m_Velocity.x = m_Direction.x * m_MoveSpeed;
	enemy_pos += m_Velocity;
	transform.SetPosition(enemy_pos);
	//MoveLeft = false;
}

Enemy::~Enemy()
{

}