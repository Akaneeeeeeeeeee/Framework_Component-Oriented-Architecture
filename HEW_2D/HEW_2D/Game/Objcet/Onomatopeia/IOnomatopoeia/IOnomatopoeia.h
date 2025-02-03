#pragma once
#include "../../BaseObject/GameObject.h"



/**
 * @brief 擬音クラス（基底クラス）
 *
 *
 * 同音異義語があるので複雑
 * →別画像と別アクションが必要
 * 
 * ・音のデータ(意味の数だけ)
 * ・擬音一つにつき１つ以上の動きがある
 * 
 * ・擬音は付与された親オブジェクトに影響を与える
*/
class IOnomatopoeia : public GameObject
{
public:

	virtual ~IOnomatopoeia() {};
	// 擬音がオブジェクトに与える動き(ここで画像の動きをいじる)
	virtual void Action(void) = 0;		// マガジンが親の場合は効果を与えない
	virtual void Fade_in_out(void);		// 擬音のフェードイン/フェードアウト
	virtual void Update(void) override;	// 更新
	virtual void Set_Onomatope(bool) = 0;   //擬音のフラグセット
	virtual bool Get_Onomatope(void) = 0;   //擬音のフラグゲット
	virtual void Set_gion(bool) = 0;
	virtual bool Get_gion(void) = 0;

protected:
	// コンストラクタをprotectedにすると派生クラスからしかコンストラクタを動かせない
	// →このクラスの親クラスのGameObjectクラスは実体を作れるが、このクラスを継承した擬音クラス達はIOnomatopoeiaとして実体を持つことはできなくなる
	IOnomatopoeia(D3D11& _D3d11) :GameObject(_D3d11) {

	};
	// 擬音が付与されているオブジェクトはGameObjectクラスのm_pParentで判断する
	std::string m_Name;				// 擬音の名前
	bool fade_check = false;
	bool Collision_Onomatope = false; //擬音がオブジェクトに付与されているかの判断フラグ
	bool Collision_gion = false;
};

