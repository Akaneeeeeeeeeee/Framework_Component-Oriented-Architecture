#include "PataPata.h"
#include "../../../../Framework/Component/Collider/BoxCollider2D/Collider.h"
#include "../../Player/Player.h"


/**
 * @brief 更新
 * 
 * オブジェクトもしくはプレイヤーに付与されている時のみ、毎フレーム少しずつ上に浮き上がり、オブジェクトに付与されているときは少し浮き上がった後下降する、を繰り返
*/
void PataPata::Update(void)
{
	// この擬音の親オブジェクトが
	if (true)
	{

	}
}


void PataPata::Action(void)
{
	
}


void PataPata::Action(std::weak_ptr<GameObject> obj, std::weak_ptr<Player> player)
{
	Vector3 patapata_pos = obj.lock()->GetPosition();
	Vector3 player_pos = player.lock()->GetPosition();
	auto patapataShared = obj;
	auto playerShared = player;

	//フラグがTRUEなら（擬音が当たっているか）
	if (Collision_Onomatope)
	{
		if (patapata_pos.y <= Max_altitude)
		{
			if (Collider_toGround(obj, player))
			{
				player_pos.y += 5;
				player.lock()->SetPosition(player_pos);
			}
			patapata_pos.y += 5;
			
			obj.lock()->SetPosition(patapata_pos);
			
		}
		else {
			Collider_check = false;
		}
	}

}


//擬音のセッター
void PataPata::Set_Onomatope(bool _flg)
{
	Collision_Onomatope = _flg;
}

//擬音のゲッター
bool PataPata::Get_Onomatope(void)
{
	return Collision_Onomatope;
}

void PataPata::Set_gion(bool _flg)
{
	Collision_gion = _flg;
}

bool PataPata::Get_gion(void)
{
	return Collision_gion;
}


PataPata::~PataPata()
{

}