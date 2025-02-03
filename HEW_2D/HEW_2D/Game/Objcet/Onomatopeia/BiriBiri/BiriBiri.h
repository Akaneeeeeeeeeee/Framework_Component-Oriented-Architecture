#pragma once
#include "../IOnomatopoeia/IOnomatopoeia.h"

class BiriBiri :public IOnomatopoeia
{
public:
	BiriBiri(D3D11& _D3d11) :IOnomatopoeia(_D3d11) {
		knockback_power = 10;
		BiriBiri_check = false;
	}
	~BiriBiri();	//デストラクタ
	void Action(void) {};
	void Action(std::weak_ptr<GameObject>);		//ビリビリ特性の関数

	bool BiriBiri_check;
	void Set_Onomatope(bool)override;//擬音のAction関数を動かすためのゲッター、セッター
	bool Get_Onomatope(void)override;
	void Set_gion(bool)override;
	bool Get_gion(void)override;
private:
	float knockback_power;//ノックバックパワー
};
