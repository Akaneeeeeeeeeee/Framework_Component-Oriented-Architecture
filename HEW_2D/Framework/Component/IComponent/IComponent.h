#pragma once
#include "../../../Game/EntryPoint/main.h"

/// <summary>
/// 全てのコンポーネントの元となるクラス
/// コンポーネントはそれをアタッチ（取りつけ）するオブジェクトがあるのでメンバ変数としてGameObjcetクラスのポインタを持つ
/// →それによってコンポーネントからアタッチしているオブジェクトにアクセスすることができる
/// </summary>

class GameObject;

class IComponent :public std::enable_shared_from_this<IComponent>
{
public:
	IComponent();
	virtual ~IComponent();

	virtual void Init(void) = 0;		// 初期化
	virtual void Update(void) = 0;		// 更新
	virtual void Uninit(void) = 0;		// 終了

	void SetOwner(const GameObject& _obj) const;	// オブジェクトのアタッチ(参照渡し)
	GameObject* GetOwner(void);						// アタッチ先のオブジェクトの取得
	//void RemoveOwner(void);			// アタッチされているオブジェクトからの取り外し

protected:
	// コンポーネントマネージャがshared_ptrで管理してるので、ここで参照を使うとオブジェクトが消えた場合参照が消えてしまうのでNG→ポインタで管理
	// 参照→nullを使えない→オブジェクトの方が先に削除された場合、未定義動作になるかもなので×
	// unique,shared→コンポーネントがオブジェクトの主有権を持つ必要がないので×
	// →ポインタにする
	GameObject* m_pOwner;				// アタッチされているオブジェクトのポインタ(単一なのでunique_ptr？)
};



