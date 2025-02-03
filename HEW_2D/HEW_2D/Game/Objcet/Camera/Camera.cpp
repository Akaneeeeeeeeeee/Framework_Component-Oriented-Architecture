#include "Camera.h"


void Camera::Update(void)
{
	// フェード中で
	if (OnFade)
	{
		// フェードインしているときは
		if (FadeIn)
		{
			// 画像の透明度を下げていく
			Color newcol = m_Color;
			newcol.w -= 0.01f;
			m_Color = newcol;
			// 明転しきったら
			if (m_Color.w < 0.0f)
			{
				// 透明度を0で固定
				m_Color.w = 0.0f;
				OnFade = false;		// フェードインに変更
				FadeIn = false;		// フラグをフェードアウトに変更
				//IsMoving = true;	// カメラ移動開始
			}
		}
		// フェードアウト中は
		else
		{
			// 画像の透明度を上げていく
			Color newcol = m_Color;
			newcol.w -= 0.01f;
			m_Color = newcol;
			// 暗転しきったら
			if (m_Color.w > 1.0f)
			{
				// 透明度を1で固定
				m_Color.w = 1.0f;
				OnFade = false;		// フェードイン
				FadeIn = true;		// フラグをフェードインに変更
				//IsMoving = false;	// カメラ移動を停止
			}
		}
	}

	// フェードアウト→カメラ座標移動→フェードイン、という風にしたい
	if (IsMoving)
	{
		// 座標を変更
		Vector3 newpos = transform.GetPosition();
		newpos.x += transform.GetScale().x;			// 1920加算する
		transform.SetPosition(newpos);

		IsMoving = false;		// 移動完了	
		OnFade = true;			// フェードアウト開始
	}
}