#pragma once
#include "../../../Game/EntryPoint/main.h"

/// <summary>
/// 全てのコンポーネントの元となるクラス
/// コンポーネントはそれをアタッチ（取りつけ）するオブジェクトがあるのでメンバ変数としてGameObjcetクラスのポインタを持つ
/// →それによってコンポーネントからアタッチしているオブジェクトにアクセスすることができる
/// </summary>

class GameObject;

class IComponent
{
public:
	IComponent();
	virtual ~IComponent();

	virtual void Init(void) = 0;		// 初期化
	virtual void Update(void) = 0;		// 更新
	virtual void Uninit(void) = 0;		// 終了

	void SetOwner(GameObject& _obj);	// オブジェクトのアタッチ(参照渡し)
	GameObject* GetOwner(void);			// アタッチ先のオブジェクトの取得
	//void RemoveOwner(void);			// アタッチされているオブジェクトからの取り外し

protected:
	// コンポーネントマネージャがshared_ptrで管理してるので、ここで参照を使うとオブジェクトが消えた場合参照が消えてしまうのでNG→ポインタで管理
	GameObject* m_pOwner;				// アタッチされているオブジェクトのポインタ(単一なのでunique_ptr？)
};



