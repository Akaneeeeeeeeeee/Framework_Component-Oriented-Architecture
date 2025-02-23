#pragma once
#include "../../Framework/Scene/IScene.h"


/**
 * @brief タイトルシーンクラス
 *
 * サウンド、背景などのゲームオブジェクトを配列（array）で持つ
 *
 * オブジェクトをコンストラクタで代入しておき、シーンの初期化処理内でオブジェクトを初期化する
*/
class TitleScene :public IScene
{
public:
	TitleScene() :IScene() {
		// オブジェクトの追加はシーンの初期化で行う
		// サウンドとかこのシーンのみ存在するものがあればその初期化を行う
	};
	~TitleScene() {};
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;

	void Title_Onomatope_Move(std::weak_ptr<Object>,float); //TitleSceneの装飾用の擬音の動き

protected:
	
};
