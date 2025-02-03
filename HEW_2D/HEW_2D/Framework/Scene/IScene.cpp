#include "IScene.h"

/**
 * @brief シーン遷移確認関数
 * @return シーン遷移フラグ
*/
bool IScene::GetChangeScene(void)
{
	return ChangeScene;
}

void IScene::SetChangeScene(bool _Flg)
{
	ChangeScene = _Flg;
}

/**
 * @brief 遷移先を確認する関数
 * @return 遷移先のシーン名
*/
SceneName IScene::GetRequestScene(void)
{
	return m_RequestNext;
}