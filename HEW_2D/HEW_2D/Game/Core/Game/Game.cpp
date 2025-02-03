#include "Game.h"
#include"../../../Framework/Input/Input.h"

/**
 * @brief
 * @param
*/
void Game::Init(void)
{
	// シーンマネージャ、サウンドの初期化
	Sound::GetInstance().Init();
	scenemanager.Init();
}


/**
 * @brief ゲームのループ処理
 * 主なゲーム処理はここに書く
*/
void Game::Update(void)
{
	// ゲーム終了フラグが立っていない場合
	if (!scenemanager.GetIsQuit())
	{
		// イベント発生まではループし続ける
		scenemanager.Update();
	}
	// ゲーム終了フラグが立ったら
	else
	{
		// 「終了しますか？」を表示して
		PostMessage(Window::GetInstance().GetHandleWindow(), WM_CLOSE, 0, 0);
		// ゲーム終了フラグをリセット
		// TODO:2025/01/30 赤根 ウィンドウメッセージを出力させてからのコントローラの入力を取得できていない
		scenemanager.SetIsQuit(false);
	}
}

void Game::Draw(void)
{
	scenemanager.Draw();
}

void Game::Uninit(void)
{
	scenemanager.Uninit();
	//Sound::GetInstance().Uninit();
}
