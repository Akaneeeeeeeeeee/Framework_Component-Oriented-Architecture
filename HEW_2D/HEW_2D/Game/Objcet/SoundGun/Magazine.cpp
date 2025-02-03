#include"Magazine.h"

/**
 * @brief 擬音装填
 * @param _onomatopoeia 装填する擬音
 *
 * 擬音を装填したい→擬音もオブジェクトマネージャで管理する→shared_ptrで管理してるので、関数で所有権をマガジンにも渡す
*/
//void Magazine::SetOnomatopoeia(Tag, std::string, std::shared_ptr<GameObject>&& _onomatopoeia)
//{
//	// 所有権を移動
//	m_Onomatopoeia = (_onomatopoeia);
//
//}


/**
 * @brief 更新
 *
 * 自身のタグがUIなら重力加速度を受けない、とかにしたかった
 * →無理なので、親オブジェクトがいる場合、重力加速度を受けない、とする
 *
 *
*/
void Magazine::Update(void)
{
	// 親オブジェクトがいない場合
	if (!m_pParent.lock())
	{
		// 重力加速度の影響を受ける
		if (!OnGround)
		{
			// 接地していなければ加算
			m_Velocity.y -= 0.5f;
		}
		else {

		}
	}


	// 移動処理
	Vector3 newpos = transform.GetPosition();
	newpos += m_Velocity;		// 方向ベクトルとX成分の移動速度を掛けた値の分だけ毎フレーム進む
	// 新しい座標を代入
	transform.SetPosition(newpos);
}


/**
 * @brief 描画
*/
void Magazine::Draw(void)
{
	// 先にマガジンを描画
	this->GameObject::Draw();

	// 次に擬音が入っていれば擬音を描画
	if (m_Onomatopoeia)
	{
		m_Onomatopoeia->Draw();
	}
}


/**
 * @brief 装填されている擬音を返す関数
 * @return 擬音の生ポインタ(所有権の移動はないので生ポを渡して管理する)
*/
IOnomatopoeia* Magazine::GetBulletPointer(void)
{
	return m_Onomatopoeia.get();
}


/**
 * @brief マガジンに擬音を装填する関数
 * @param _onomat 擬音
*/
void Magazine::SetOnomatopoeia(std::shared_ptr<IOnomatopoeia> _onomat)
{
	// マガジンに装填
	m_Onomatopoeia = _onomat;
	// 擬音をマガジンの子オブジェクトに設定
	SetChild(_onomat);
}


/**
 * @brief 発射時に擬音の所有権を擬音銃に渡してマガジン内を空にする関数
 * @return 擬音のポインタ
*/
std::shared_ptr<IOnomatopoeia> Magazine::ReleaseBullet(void)
{
	// 所有権を委譲
	return std::move(m_Onomatopoeia);
}
