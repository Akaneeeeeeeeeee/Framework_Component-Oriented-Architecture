#pragma once
#include "../../EntryPoint/main.h"
#include "../../../Framework/D3D11/D3D11.h"
#include "../../../Framework/WICTextureLoader/WICTextureLoader.h"	// テクスチャ読み込みライブラリ
#include "../../../Framework/Component/Transform/Transform.h"		//Transform.h読み込み

/// <summary>
/// TODO:オブジェクトの描画方法を変更する
/// 
/// 現在：頂点バッファのみで描画
/// 目標：インデックスバッファを使用した描画に変更
/// 
/// 良い点：頂点情報を共有できるので規模が大きくなればなるほど描画処理の負荷が減る
/// 
/// --------------改善案----------------
/// d3dクラスのポインタ→参照？ユニークポインタ？d3dクラスをstatic化？Rendererクラス作成？
/// 
/// オブジェクトが持つもの
/// ・コンポーネントマネージャ
/// ・名前
/// ・タグ
/// 
/// 
/// 現状：TransformとRigidBody、描画機能(Renderer?程度のもの)が付いたくらいの状態
/// 
/// 
/// </summary> 

/**
 * @brief オブジェクト管理タグ
*/
enum Tag {
	BACKGROUND,
	IMAGE,
	UI,
	OBJECT,
	GROUND,
	ONOMATOPOEIA,
	PLAYER,
	ENEMY,
	CAMERA
};

// オブジェクトの状態（ここに全部書き出しておく）
enum STATE
{
	NORMAL,		// 通常時
	RUN,		// 移動時
	JUMP,		// ジャンプ時
	DAMAGED,	// 被ダメ時
	ATTACKED,	// 攻撃時
	EFECT,      //エフェクト
};

/**
 * @brief アニメーション番号管理用構造体
*/
struct Int2 {
	int x;
	int y;

	// コンストラクタ
	Int2(int _x = 0, int _y = 0) : x(_x), y(_y) {};

	// 演算子オーバーロード
	// 加算
	Int2 operator + (const Int2& other) const {
		return Int2(x + other.x, y + other.y);
	}

	// 減算
	Int2 operator - (const Int2& other) const {
		return Int2(x - other.x, y - other.y);
	}
};

class IOnomatopoeia;

/**
 * @brief 基本となるゲームオブジェクトクラス
 * 
 * std::enable_shared_from_this:自身のshared_ptrを生成するために必要
 * 
 * 一旦コンポーネント指向ではなくオブジェクト指向で止めておく
 * @param vertices 頂点データ
 * @param d3d11 d3dクラスのポインタ（描画に使用）
 * @param transform トランスフォーム（座標、回転、大きさ）
 * @param color 色情報
 * 
*/
class GameObject :public std::enable_shared_from_this<GameObject>
{
protected:
	//! 頂点データ
	//! このゲームでは擬音を吸い込むことがあるため頂点を可変にしておく
	std::vector<Vertex> vertices;
	
	// d3dクラス
	D3D11& D3d11;

	// 座標,大きさ,角度
	Transform transform;
	
	// 色
	Color m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	
	// テクスチャ用変数
	ID3D11ShaderResourceView* m_pTextureView = nullptr;

	//テクスチャが縦横に何分割されているか
	Int2 m_Split = { 1,1 };

	//左上から何段目を切り抜いて表示するか
	Int2 m_Number = { 0,0 };

	// アニメーション用状態管理変数
	STATE m_State = {};

	// アニメーション管理フラグ
	bool IsAnimation = false;

	// 接地しているか？
	bool OnGround = false;

	// 削除予定フラグ(毎フレームこのフラグを確認し、立っているオブジェクトは削除する)
	bool IsDelete = false;

	// 親オブジェクトのポインタ(子は親の所有権は持たないのでweak_ptrでおｋ)
	std::weak_ptr<GameObject> m_pParent;

	// 子オブジェクトのポインタ(親は子の所有権を持つのでshared_ptrにする)
	std::vector<std::shared_ptr<GameObject>> m_pChildren;		// 子は複数存在する可能性があるのでvector

	// 速度(これは毎フレーム変化する値)
	Vector3 m_Velocity;

	// 加速度(それぞれの軸の方向の加速度(重力とか)を設定→毎フレーム一定の値(現実だと時間)を乗算した値を速度に代入する、というように使う)
	//Vector3 m_Acceleration;→速度から算出できるのでいらない

	// 移動用方向ベクトル(Transform.Rotaionは回転を扱うものなので別物)
	Vector3 m_Direction;

	// 付与されている擬音
	std::shared_ptr<IOnomatopoeia> m_AttachedOnomatopoeia;

	//// 名前(一意のもの)
	//std::string m_Name;

	//// タグ(オブジェクトの分類)
	//Tag m_Tag;

public:
	ConstBuffer cb;


	//GameObject() = default;	// クラスのメンバ変数に参照が入っている場合、デフォルトコンストラクタが使えない（初期化が必須となる）
	GameObject(D3D11& _D3d11);
	virtual ~GameObject();

	virtual void Init(const wchar_t* imgname, int sx = 1, int sy = 1, bool _animation = false); // 初期化
	virtual void Update(void);						// 更新（自オブジェクトに”何か”が当たった判定だけここで確認）
	virtual void Draw(void);						// 描画
	virtual void Uninit(void);						// 終了
	virtual void SetPosition(Vector3 _Pos);			// 座標をセット
	virtual void SetScale(Vector3 _Size);			// 大きさをセット
	virtual void SetRotation(Vector3 _Rot);			// 角度をセット
	virtual void SetColor(const Color _Color);	// 色をセット
	virtual void SetUV(const Int2 _UV);			// UV座標をセット
	virtual void Animation(STATE,std::weak_ptr<GameObject>);		// アニメーション
	// TODO:2025/01/24 赤根:プレイヤーに親子関係を持たせる際の関数の引数にタグと名前を入れるように変更する→プレイヤー側でオーバーライドして、タグがマガジンであればタグを変更、にしようと思ったが、それだとオブジェクトマネージャの管理外での処理が発生するかも→オブジェクトにはオブジェクトのポインタだけを持たせたほうが良いかも
	virtual void SetParent(const std::weak_ptr<GameObject> _Parent);	// 親オブジェクトをセット
	virtual void AddForce(const Vector3 _Vel);		// 速度をセット(ここでは即座に値を加算する方法だけ作る→unityのforcemode.impulseみたいなやつ)
	virtual void SetDirection(Vector3 _Dir);		// 方向ベクトルをセット
	virtual void SetOnGround(bool _flg);			// 接地しているか？
	virtual void SetIsDelete(bool _flg);			// 削除予定セット
	virtual void SetChild(const std::shared_ptr<GameObject> _Child);		// 子オブジェクトをセット

	// 個別の当たり判定もここに追加？オブジェクトの基本となるクラスならここじゃなくて、判定が必要なオブジェクトにそれぞれ追加？

	virtual Vector3 GetPosition(void);		// 座標を取得
	virtual Vector3 GetScale(void);			// 大きさを取得
	virtual Vector3 GetRotation(void);		// 角度を取得
	virtual Color GetColor(void);			// 色を取得
	virtual Int2 GetUV(void);				// UV座標を取得
	virtual Vector3 GetVelocity(void);		// 速度を取得
	virtual Vector3 GetDirection(void);		// 方向ベクトルを取得
};
