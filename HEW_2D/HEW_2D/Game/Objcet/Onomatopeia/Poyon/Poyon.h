#pragma once
#include "../IOnomatopoeia/IOnomatopoeia.h"
#include "../../Player/Player.h"



/**
 * @brief ポヨン（飛び跳ねる）
 *
 * 付与されたオブジェクトの弾力を高める
 * →velocityを高める
 * 　→当たったら跳ね返す
 * 
 * 
 * 付与されたオブジェクトに当たったものを弾き返す
 * →どこに当たってるかを判定して、当たったオブジェクトにその向きの力を加える
*/
class Poyon : public IOnomatopoeia
{
public:

	Poyon(D3D11& _D3d11) :IOnomatopoeia(_D3d11) {

	}

	~Poyon();
	void Action(void) {};
	void Action(std::weak_ptr<Player>);
	void Set_Onomatope(bool)override;//擬音のAction関数を動かすためのゲッター、セッター
	bool Get_Onomatope(void)override;
	void Set_gion(bool)override;
	bool Get_gion(void)override;
private:

};


