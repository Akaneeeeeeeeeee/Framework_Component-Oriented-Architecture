#include "CrossHair.h"

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
		transform.SetPosition(newpos);
	}
	// 右移動
	if (MoveRight)
	{
		newpos.x += m_Velocity.x;
		transform.SetPosition(newpos);
	}
	// 上移動
	if (MoveUp)
	{
		newpos.y += m_Velocity.y;
		transform.SetPosition(newpos);
	}
	// 下移動
	if (MoveDown)
	{
		newpos.y -= m_Velocity.y;
		transform.SetPosition(newpos);
	}
}
