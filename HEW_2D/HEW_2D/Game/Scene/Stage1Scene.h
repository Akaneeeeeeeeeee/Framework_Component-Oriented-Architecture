#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../../Framework/Sound/sound.h"
#include "../../Framework/D3D11/D3D11.h"


/**
 * @brief タイトルシーンクラス
 * 
 * サウンド、背景などのゲームオブジェクトを配列（array）で持つ
 * 
 * オブジェクトをコンストラクタで代入しておき、シーンの初期化処理内でオブジェクトを初期化する
*/
class Stage1Scene :public IScene
{
public:
	Stage1Scene(D3D11& _D3d11) :IScene(_D3d11) {
		// オブジェクトの追加はシーンの初期化で行う
		// サウンドとかこのシーンのみ存在するものがあればその初期化を行う
		ChangeScene = false;
		CurrentFrame = FRAME1;	// 現在フレームをフレーム1に
		OldFrame = FRAME_MAX;	// 一フレーム前はなし
	};
	~Stage1Scene() {};
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;

	void Frame2Init(void);
	void Frame3Init(void);
	void Frame4Init(void);


private:
	FRAME CurrentFrame;		// 現在のフレーム
	FRAME OldFrame;			// 一フレーム前のフレーム

};



// 289～317 スライム挙動
// 539～612 擬音挙動