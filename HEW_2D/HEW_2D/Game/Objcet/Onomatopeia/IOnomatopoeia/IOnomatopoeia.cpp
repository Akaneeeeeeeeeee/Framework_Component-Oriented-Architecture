#include "../IOnomatopoeia/IOnomatopoeia.h"
#include "../../BaseObject/GameObject.h"



/**
 * @brief フェードイン/フェードアウト（時間経過で取るか検討中）
 * 現状は擬音出現中はフェードイン/アウトを繰り返す→擬音が鳴った時に実行するようにしたい
*/
void IOnomatopoeia::Fade_in_out(void)
{
	Color c_obj = m_Color;
	if (fade_check)
	{
		c_obj.w += 0.03f;
		if (c_obj.w >= 1.0f)
		{
			c_obj.w = 1.0f;
			fade_check = false;
		}
		m_Color = c_obj;
	}
	else {
		c_obj.w -= 0.03f;
		if (c_obj.w <= 0.0f)
		{
			c_obj.w = 0.0f;
			fade_check = true;
		}
		m_Color = c_obj;
	}
}



/**
 * @brief 更新
*/
void IOnomatopoeia::Update(void)
{
	// 力が加えられている場合、その方向へ進むようにする(減速とかは特になし)
	this->GameObject::Update();
}
