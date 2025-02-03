#pragma once
#include "../../../Game/SceneManager/SceneManager.h"
#include "../../../Framework/D3D11/D3D11.h"
#include"../../../Game/Scene/Stage1Scene.h"
#include "../../../Framework/Sound/sound.h"



//class D3D11;

/**
 * @brief ゲームクラス
 * アプリケーションクラスが保持するゲームクラス
 * →このクラスを切り替えれば他のゲームでもこの外側のクラスは使いまわせる
*/
class Game
{
public:
	Game(D3D11& _D3d11) :scenemanager(_D3d11) {};
	~Game() {};

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

private:
	SceneManager scenemanager;	// シーン管理クラス

};
