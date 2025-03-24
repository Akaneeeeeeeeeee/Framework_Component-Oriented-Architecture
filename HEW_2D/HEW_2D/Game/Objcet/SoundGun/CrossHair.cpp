#include "CrossHair.h"


CrossHair::CrossHair(const UINT& _ID, const Tag& _tag, const std::string& _name) : Object(_ID, _tag, _name) {
	MoveLeft = false;
	MoveRight = false;
	MoveUp = false;
	MoveDown = false;
	GetComponent<RigidBody2D>()->AddForce(Vector3(10.0f, 0.0f, 0.0f), ForceMode2D::VelocityChange);	// クロスヘアの移動速度
}

/**
 * @brief 更新
*/
void CrossHair::Update(void)
{
	// 座標設定用変数
	Vector3 newpos = transform.GetPosition();

	// 左移動
	if (MoveLeft)
	{
		newpos.x -= m_Velocity.x;
	}
	// 右移動
	if (MoveRight)
	{
		newpos.x += m_Velocity.x;
	}
	// 上移動
	if (MoveUp)
	{
		newpos.y += m_Velocity.y;
	}
	// 下移動
	if (MoveDown)
	{
		newpos.y -= m_Velocity.y;
	}
	transform.SetPosition(newpos);
}
