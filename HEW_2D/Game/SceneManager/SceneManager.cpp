#include "SceneManager.h"
#include "../../Game/Scene/StageSelectScene.h"
#include "../../Game/Scene/Stage1Scene.h"
#include "../../Game/Scene/Stage2Scene.h"
#include "../../Game/Scene/ResultScene.h"
#include "../../Game/Scene/GameScene.h"
#include "../../Game/Scene/TitleScene2.h"
#include "../../Game/Scene/TestScene.h"

/**
 * @brief シーン配列初期化
*/
void SceneManager::Init(void) 
{
	//! タイトルシーンを生成してコンテナに追加
	Scenes.emplace(TITLE, std::make_unique<TitleScene>(D3d11));
	//Scenes現在シーンをタイトルシーンに設定
	CurrentScene = TITLE;
	Scenes[CurrentScene]->Init();
}

/**
 * @brief 更新
*/
void SceneManager::Update(void)
{
	// 現在シーンの更新
	Scenes[CurrentScene]->Update();

	// 流れ
	// 現在シーンで設定されている遷移先シーンを確認→そのシーンに遷移
	// →同じシーンに飛ぼうとしてる場合は一旦フェードアウトし、そのシーンの初期化を行ってからフェードイン

	// 現在シーンの遷移フラグが立っている場合、シーン遷移
	if (Scenes[CurrentScene]->GetChangeScene())
	{
		// 現在シーンがステージ選択なら、遷移先シーン確認→遷移関数実行
		// そうでないならシーン遷移関数実行するだけ

		// 遷移先シーンを確認して遷移処理実行
		// 遷移先がゲーム終了でなければ
		if (Scenes[CurrentScene]->GetRequestScene() != QUIT)
		{
			// シーン遷移処理実行
			ChangeScene(Scenes[CurrentScene]->GetRequestScene());
		}
		// ゲーム終了が選ばれた場合
		else
		{
			// ゲーム終了フラグを立てる
			this->Quit = true;
		}
		
	}
	
}


void SceneManager::Draw(void) {
	//! 現在シーンによってそのシーンを描画
	//! →これだとシーンの解放を考えられてなくない？添え字を指定しちゃってるからvectorな意味ないかも
	//! 　→map使う？？？
	
	// 現在シーンの描画
	Scenes[CurrentScene]->Draw();
}

void SceneManager::Uninit(void) {
	// 全てのシーンの終了処理
	for (auto& scene : Scenes)
	{
		// シーンの中身を解放
		scene.second.reset();
	}
	// シーン配列全体を解放
	Scenes.clear();
}

/**
 * @brief シーン切り替え関数
 * タイトル、終了画面（？）、ステージ選択シーンはシーンとして保持し続けておきたい（頻繁に使うため、毎回生成→解放しなくても良くない？）
 * @param  次のシーンタグ
 * 
 * フェードインとかもさせたいので、その場合、
 * ・シーン切り替え→切り替えフラグを立てる
 *　 →切り替え中に次シーン生成とフェードアウト
 * 　　→フェードアウトしたら（もしくは生成完了したら）前シーン解放し、フェードイン（ここで前シーン解放）
*/
void SceneManager::ChangeScene(SceneName _Nextscene) {
	// 切り替え前のシーンステージ選択画面ではない（保持しておきたいシーンではない）場合、
	if (CurrentScene != STAGESELECT)
	{
		// 現在シーンを解放
		DeleteScene(CurrentScene);
	}

	// 切り替え予定のシーンが存在していない場合
	if (Scenes.find(_Nextscene) == Scenes.end())
	{
		// シーンを生成してmapに追加
		switch (_Nextscene)
		{
		case TITLE:
			CreateScene<TitleScene>(TITLE);
			break;
		case STAGESELECT:
			CreateScene<StageSelectScene>(STAGESELECT);
			break;
		/*case TEST:
			CreateScene<TestScene>(TEST);
			break;*/
		case STAGE1:
			CreateScene<Stage1Scene>(STAGE1);
			break;
		case STAGE2:
			CreateScene<Stage2Scene>(STAGE2);
			break;
		case RESULT:
			CreateScene<ResultScene>(RESULT);
			break;
		// ゲーム終了が選択された場合はシーン遷移処理はしないので何も書かない
		case QUIT:
			break;
		default:
			break;
		}
	}
	// 現在シーンを切り替え
	this->CurrentScene = _Nextscene;

	// 切り替えたシーンの初期化→ここ切り替え前シーンと同じシーンに以降としてる場合はもう一度プレイしようとしてるので初期化するまでにフェードアウト・イン処理とか必要
	Scenes[CurrentScene]->Init();
}

/**
 * @brief シーン取得関数
 * @param _SceneName シーンのタグ
 * @return シーンのポインタ
*/
IScene* SceneManager::GetScene(SceneName& _SceneName)
{
	// シーンのイテレータを取得
	auto iterator = Scenes.find(_SceneName);

	// シーンが見つかれば
	if (iterator != Scenes.end())
	{
		// シーンのポインタを返す
		return iterator->second.get();
	}
	// 見つからなければnullptrを返す
	return nullptr;
}

/**
 * @brief シーン削除関数
 * @param _SceneName 削除したいシーンの型（mapのキー）

*/
void SceneManager::DeleteScene(SceneName _SceneName)
{
	// 指定したシーンを削除
	Scenes.erase(_SceneName);
	std::cout << _SceneName << std::endl;
}

/**
 * @brief ゲーム終了リクエストの状態を返す
 * @return ゲーム終了状態
*/
bool SceneManager::GetIsQuit(void)
{
	return Quit;
}

/**
 * @brief ゲーム終了フラグを設定する関数
 * @param _flg
*/
void SceneManager::SetIsQuit(bool _flg)
{
	this->Quit = _flg;
}
