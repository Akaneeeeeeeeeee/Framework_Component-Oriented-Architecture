#include "Camera.h"
#include "../../../Framework/Component/Physic/RigidBody2D/RigitBody2D.h"

Camera::Camera() {
	//! カメラの移動スピード
	GetComponent<RigidBody2D>()->AddForce(Vector3(20.0f, 0.0f, 0.0f), ForceMode2D::VelocityChange);
	Vector3 scale = { 1920.0f, 1080.0f, 0.0f };
	GetComponent<TransformComponent>()->SetScale(scale);
	Vector3 pos = { 0.0f,0.0f,0.0f };
	GetComponent<TransformComponent>()->SetPosition(pos);
	//cameraSpeed = StageSize / 100;	//!ステージの移動スピード

	// 最初はフェードインから始めたいのでフェードのフラグのみを設定しておく
	OnFade = true;
	FadeIn = true;
	IsMoving = false;
}

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