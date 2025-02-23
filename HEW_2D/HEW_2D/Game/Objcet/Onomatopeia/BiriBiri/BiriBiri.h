#pragma once
#include "../IOnomatopoeia/IOnomatopoeia.h"

class BiriBiri :public IOnomatopoeia
{
public:
	BiriBiri(const UINT& _ID, const Tag& _tag, const std::string& _name) :IOnomatopoeia(_ID, _tag, _name) {
		knockback_power = 10;
		BiriBiri_check = false;
	}
	~BiriBiri();	//デストラクタ
	void Action(void) {};
	void Action(std::weak_ptr<Object>);		//ビリビリ特性の関数

	bool BiriBiri_check;
	void Set_Onomatope(bool)override;//擬音のAction関数を動かすためのゲッター、セッター
	bool Get_Onomatope(void)override;
	void Set_gion(bool)override;
	bool Get_gion(void)override;
private:
	float knockback_power;//ノックバックパワー
};
