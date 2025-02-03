#pragma once
#include "../../Framework/Scene/IScene.h"

//! TODO:scenemanagerでStage1Sceneとresultsceneをインクルードすると、それぞれでインクルードされているobjectmanagerとISceneが衝突してしまう
//! →scenemanager.cppでのみStage1Sceneとresultsceneをインクルードして解決
//! TODO:シーンをvectorで持つべき？mapで持つべき？
//! 
//! 使っていないシーンはロードせず、現在シーンだけを更新、描画するようにしたい
//! シーン遷移の時に前シーンを解放して新しいシーンを初期化、という流れにしたい
//!						↓
//! ステージ選択シーンはずっと保持しておき、選択されたステージだけを毎回生成→解放
//! という流れを取りたい
//! 
//! -----------------------------------------------------------------------------------------
//!  オブジェクト個別に描画機能を持たせているのでオブジェクトマネージャーまでd3dの参照を渡したい
//! 　→シーンマネージャまではコンストラクタで持ってこられたがオブジェクトマネージャに持っていけない
//! 　　→これより内側のクラスにはd3dの参照を持たせて解決する（もっとスマートにしたかった）
//! 　　　→時間があればRendererクラスみたいなのを作って、描画機能は全てそのクラス担当とさせるべき
//! 


/**
 * @brief シーン管理クラス
 * オブジェクト管理はタグと名前を使うが、シーンの管理はシーンの名前(こちらで定義)のみで行う
 * 
 * シーン切り替え関数が必要
*/
class SceneManager
{
public:
	SceneManager() = default;
	/**
	 * @brief コンストラクタ
	 * @param _D3d11 d3dの参照
	 * タイトルシーンはゲーム開始すぐに必要なのでコンストラクタで生成する
	*/
	SceneManager(D3D11& _D3d11) :D3d11(_D3d11)
	{
		// シーン保持しているコンテナを空にする
		Scenes.clear();
		CurrentScene = {};
		Quit = false;
	};
	~SceneManager() {};

	void Init(void);		//! 初期化
	void Update(void);		//! 更新
	void Draw(void);		//! 描画
	void Uninit(void);		//! 終了

	void ChangeScene(SceneName scene);	//! シーン切り替え

	/**
	 * @brief シーン生成関数
	 * @tparam T 生成したいシーンの型
	 * @param _name キー（シーンの名前（タグ））
	*/
	template <typename T>
	void CreateScene(SceneName _SceneName)
	{
		// タグを設定してシーンを追加
		Scenes.emplace(_SceneName, std::make_unique<T>(D3d11));
	}

	/**
	 * @brief シーン取得関数
	 * @param _SceneName シーンのタグ
	*/
	IScene* GetScene(SceneName& _SceneName);

	/**
	 * @brief シーン削除関数
	 * @param _SceneName 削除したいシーンの型（mapのキー）
	*/
	void DeleteScene(SceneName _SceneName);

	/**
	 * @brief ゲーム終了リクエストの状態を返す
	 * @return ゲーム終了状態
	*/
	bool GetIsQuit(void);

	/**
	 * @brief ゲーム終了フラグを設定する関数
	 * @param _flg 
	*/
	void SetIsQuit(bool _flg);

private:
	D3D11& D3d11;
	std::unordered_map<SceneName, std::unique_ptr<IScene>> Scenes;	//! シーン配列
	SceneName CurrentScene;
	bool Quit = false;
};




