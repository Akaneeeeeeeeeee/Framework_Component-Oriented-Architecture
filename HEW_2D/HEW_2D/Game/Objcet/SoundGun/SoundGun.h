#pragma once
#include "../BaseObject/GameObject.h"


class Magazine;

/**
 * @brief プレイヤーが持つ擬音銃クラス
 * 
 * ・機能としては吸い込み、使用の二つ
 * 　→使用する場合、使用先が決まっているなら「擬音の能力を付与」しなければならない
 * 
 * ・使用先の決定もここの機能として持つ
 * 
 * ・ステージ内でマガジン数増加予定なのでvectorでマガジンを持たせる
 * 
 * ＜必要なもの＞
*/
class SoundGun : public GameObject
{
public:
	SoundGun(D3D11& _D3d11) :GameObject(_D3d11) {
		IsSuction = false;
		IsShot = false;
		m_ShotPower = 25.0f;
	};
	~SoundGun() {};

	// TODO:2025/01/27 吸い込み関数作りきる→外側でやってるからどうするかも決める、擬音銃が吸い込み中の時だけ画像とアニメーションを回す
	// W押したらエラー吐くのを直す
	bool Suction(std::weak_ptr<GameObject> _gion);	// 吸い込み関数(吸い込む擬音のデータ、それを戻り値で渡し、マガジンに入れ込む)
	void Shot(std::shared_ptr<Magazine> _mag);		// 発射関数(選択したマガジン内の擬音を発射する)

	void SetIsSuction(bool _flg);
	bool GetIsSuction(void);
	void Update(void) override;
	void Draw(void)override;

private:
	bool IsSuction;			// 吸い込み中か？
	bool IsShot;			// 発射したか？
	float m_ShotPower;		// 射撃力
};

