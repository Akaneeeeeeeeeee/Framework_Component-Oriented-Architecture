#pragma once
#include "../../Framework/Scene/IScene.h"


/**
 * @brief ステージ選択シーン
 * このシーンはゲーム中常に保持しておく
 * 
 * 順番にステージを開けていく設計にするならそれを管理する仕組みも必要
*/
class StageSelectScene :public IScene
{
public:
	StageSelectScene(D3D11& _D3d11) :IScene(_D3d11) {
		ChangeScene = false;
	}
	~StageSelectScene() {};

	void Init(void) override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;


private:
	
};

