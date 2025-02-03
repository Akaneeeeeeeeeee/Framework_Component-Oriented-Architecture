#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../ObjectManager/ObjectManager.h"


/**
 * @brief ゲームシーン
 * 
 * シーンの派生全部テンプレートでよくないか？。。。→ポリモーフィズムで管理できないからNG!
*/
class GameScene :public IScene
{
public:
	GameScene(D3D11& _D3d11) :IScene(_D3d11) {};
	~GameScene() {};
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;

private:

};

