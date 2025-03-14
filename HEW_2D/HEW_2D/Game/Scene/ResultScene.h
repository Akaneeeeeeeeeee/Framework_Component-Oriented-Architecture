#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../ObjectManager/ObjectManager.h"

class ResultScene :public IScene
{
public:
	ResultScene() :IScene() {};
	~ResultScene() {};
	
	void Init(void) override;		//! 初期化
	void Update(void) override;		//! 更新
	void Draw(void) override;		//! 描画
	void Uninit(void) override;		//! 終了

private:
	
};
