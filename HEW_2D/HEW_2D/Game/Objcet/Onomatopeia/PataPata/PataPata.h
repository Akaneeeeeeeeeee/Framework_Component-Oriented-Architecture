#pragma once
#include "../IOnomatopoeia/IOnomatopoeia.h"


class Player;

/**
 * @brief パタパタ(羽ばたき)
 * 
 * TODO:2025/01/25 赤根 現状擬音のAction関数の引数に擬音の影響を受けるオブジェクトのポインタを渡してるので、引数なしで実行できるようにする
 * →直接付与されているオブジェクトのみで完結できるようにする
 * 
 * ＜付与されたオブジェクトの動き＞
 * ・移動速度の分だけ毎フレーム移動する
 * ・付与されたオブジェクトは毎フレームふわっと浮き上がれる(プレイヤーに付与した場合、ジャンプボタンを押している間は浮き上がり続ける、など)
 * →毎フレームほんの少しだけ上向きに力を加える→オブジェクトは移動しないので横向きの方向ベクトルが加えられることはなく、斜めに移動することはない
 * 
*/
class PataPata :public IOnomatopoeia
{
public:
	PataPata(D3D11& _D3d11) :IOnomatopoeia(_D3d11) {
		Max_altitude = 300.0f;		// 限界高度仮設定(Y:+400)
		Collider_check = false;
	}
	~PataPata();	//デストラクタ
	void Update(void) override;
	void Action(void) override;		// 付与されたオブジェクトに効果を与える
	void Action(std::weak_ptr<GameObject>, std::weak_ptr<Player>);	//オーバーロード
	void Set_Onomatope(bool)override; //擬音のAction関数を動かすためのゲッター、セッター
	bool Get_Onomatope(void)override;
	void Set_gion(bool)override;
	bool Get_gion(void)override;

private:
	bool Collider_check;
	float Max_altitude;		//限界高度
};
