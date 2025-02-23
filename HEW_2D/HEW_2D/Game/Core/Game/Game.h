#pragma once
#include "../../../Game/SceneManager/SceneManager.h"
#include "../../../Framework/Graphics/Graphics.h"
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
	Game() :scenemanager() {};
	~Game() {};

	void Init(void);
	void Update(void);
	void Draw(void);
	void Uninit(void);

private:
	SceneManager scenemanager;	// シーン管理クラス

};
