#pragma once
#include "../SoundGun/SoundGun.h"
#include "../Character/Character.h"
#include "../SoundGun/Magazine.h"
#include "../SoundGun/CrossHair.h"



/**
 * @brief プレイヤークラス
 * 
 * ＜必要なもの＞
 * ・移動速度
 * ・ジャンプ力
 * ・当たり判定
 * 
 * 
 * ↓の二つはプレイヤーのメンバとして持たせるのではなく、シーン内でオブジェクトマネージャからAddObjectを行い、そこから親オブジェクトとしてプレイヤーをセットする
 * ・擬音銃
 * ・マガジン
 * 
 * マガジン→取ったら画像出現→以降は擬音が入っていなくても画像が見える用にする
 * 
 * アニメーション問題：キャラごとにステート（状態）を持たせておき、その状態に応じたアニメーションを動かす
 * 
 * アニメーション
 * アクション実行中の場合毎フレームスプライト切り替えたい
 * →ボタン押してる時はアクション中
 * 
 * 
 * マガジンをもち、プレイヤーの描画で全て描画すればいいはず！！
 * →画像(シェーダーリソースビューとか？)を配列にするべきか？
 * 
*/

class Magazine;

class Player :public Character
{
public:
	Player(D3D11& _D3d11) :Character(_D3d11) {
		m_Velocity = { 0.0f };
		m_MoveSpeed = 5.0f;
		m_JumpPower = 10.5f; //7.5
		IsShot = false;
		IsSuction = false;
		m_Soundgun = nullptr;
		m_Magazines.clear();
		UseMagNumber = 1;		// 0番目のマガジンはドォン専用なので1番目からスタート
		BombCount = 0;
	};

	/**
	 * @brief デストラクタ
	*/
	~Player() {
		Uninit();
	};
	
	void Update(void) override;		// プレイヤー固有の入力はここで取得する
	void Draw(void) override;		// 擬音使用で描画方法変更があった場合用に宣言
	void Uninit(void) override;		// 解放

	void Animation(STATE _Anim_Name);	// プレイヤー個別のアニメーション関数

	void SetChild(const std::shared_ptr<GameObject> _child) override;

	// マガジンを取得したときに、UIとして表示する座標を設定したい→既に取得してUIとして表示されているマガジンの座標横に配置する→マガジンの座標が欲しい
	//void SetMagazine(std::shared_ptr<Magazine> _mag);

	// TODO:2025/01/27 擬音銃クラスで吸い込み関数作成→プレイヤーの吸い込みではそれを実行し、その関数の戻り値で吸い込んだ擬音を返し、マガジンにセットすれば行けるはず
	
	// TODO:2025/01/28 移動しながら吸い込んだらうまく吸い込まれないバグを直す。吐きだし処理を完成させる
	bool Suction(std::weak_ptr<GameObject>);	// 吸い込み関数(戻り値で吸い込み処理が終了したかを判定)
	void Shot(void);		// 擬音の発射関数

	void SetIsShot(bool _flg);
	bool GetIsShot(void);
	void SetIsSuction(bool _flg);
	bool GetIsSuction(void);

	// 撃とうとしている(選択されているマガジン内にある)擬音の情報を渡す関数
	IOnomatopoeia* GetLoadedBullet(void);

	// 銃に装填されているマガジンを返す関数
	std::shared_ptr<Magazine> GetUsingMag(void);

	int GetMagNumber(void);
	void SetMagNumber(int _num);

	// マガジン数を返す
	size_t GetMagCount(void);

private:
	bool IsSuction;		// 吸い込み中か？
	bool IsShot;		// 発射中か？
	int UseMagNumber;	// マガジンの何番目を使う(装填する)か
	int BombCount;		// ドォンのカウント
	// 擬音銃(吸い込む竜巻画像を持たせるために使う→シェーダーリソースビューとかを配列にすれば画像は複数読み込めたかも)
	std::shared_ptr<SoundGun> m_Soundgun;		// 擬音銃
	std::vector<std::shared_ptr<Magazine>> m_Magazines;	// マガジン（可変長）,0番目はドォン専用にして、その後はカウントを増やしてドォンを管理する？
	std::shared_ptr<CrossHair> m_CrossHair;		// クロスヘア
};

