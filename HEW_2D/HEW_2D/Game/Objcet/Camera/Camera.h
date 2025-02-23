#pragma once
#include "../BaseObject/Object.h"

/**
 * @brief カメラクラス
 * 
 * ＜必要なもの＞
 * 　・描画したい画面の大きさ(幅、高さ)
 * 　・カメラの座標(注視点はゲーム的に必要なさそう)
 * 　・描画機能
 * 
 * ・時間がないので今回のカメラは黒の画像を持った普通のオブジェクトとする
 * 
 * こんなところか？当たり判定もいらないし
 * →で、カメラ画面内にあるモノだけ描画する、とすれば行けるはず
*/
class Camera : public Object
{
public:
	Camera() :Object() {
		//! カメラの移動スピード
		GetComponent<RigidBody2D>()->AddForce(Vector3(20.0f,0.0f,0.0f),ForceMode2D::VelocityChange);
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

	~Camera() {};
	
	void Update(void);		//! カメラスピードとオブジェクトの位置
	void SetIsMoving(bool _flg) { IsMoving = _flg; }

private:
	bool OnFade;	// フェード中
	bool FadeIn;	// フェードイン/アウト判定
	bool IsMoving;	// 移動中か判定
};

