#pragma once
#include "../../../Framework/D3D11/D3D11.h"
#include "../../../Framework/Window/Window.h"
#include "../Game/Game.h"


/**
 * @brief ゲームそのものを管理するクラス（Applicationクラス?）
 * 
 * 流れとしては、
 * ①windowの初期化をする
 * ②HWND（ウィンドウの情報持ってるアドレスへのポインタみたいなもの）を使ってコンストラクタでDirectXの初期化をする
 * ③ゲームの中身の初期化をする
 * という流れで進む。普通に考えれば終了処理はその逆の順番なはず
 * 
 * InputとWindowクラスはシングルトンとして設計
*/
class Application {
private:
	D3D11 m_D3d11;			// DirectX11管理クラス
	//Window window;		// ウィンドウクラス
	Game m_Game;			// ゲームクラス
public:
	//! メンバ変数は宣言した順に初期化される→先にd3d11のコンストラクタを呼び出し、そのあとにgameクラスのコンストラクタを呼ぶ
	Application() :m_D3d11(), m_Game(m_D3d11) {};
	~Application() {};


	void Init(void);		// 初期化
	void Run(void);			// ループ
	void Uninit(void);		// 終了
};
