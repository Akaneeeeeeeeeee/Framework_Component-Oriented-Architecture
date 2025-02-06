#include "RigitBody2D.h"

/**
 * @brief 初期化
 * @param  
*/
void RigidBody2D::Init(void)
{

}

/**
 * @brief 更新
 * 
 * 物理計算の順番は、
 * １：力
 * ２：加速度
 * ３：速度
 * ４：位置
 * なのでその順番で計算する
 * 
 * TODO:2025/0206 物理演算の仕組みを理解する
 * 
*/
void RigidBody2D::Update(void)
{
	// 力の計算
	// force に 重力による力（F = m * g） を加算する
	// force は 次のフレームの加速度計算に使う
	m_Force += m_Mass * m_GravityScale;

	// 加速度を求める
	Vector3 acceleration = m_Force / m_Mass;
}

/**
 * @brief 終了
 * @param  
*/
void RigidBody2D::Uninit(void)
{
	// アタッチされているオブジェクトのポインタをnullptrに
	m_pOwner = nullptr;
}

/**
 * @brief 力を加える関数
 * @param _force 加える力
 * @param _mode 力の加え方(デフォルトはForce)
*/
void RigidBody2D::AddForce(Vector3 _force, ForceMode _mode = ForceMode::Force)
{
	switch (_mode)
	{
	case ForceMode::Force:
		break;
	case ForceMode::Acceleration:
		break;
	case ForceMode::Impulse:
		break;
	case ForceMode::VeclocityChange:
		break;
	default:
		break;
	}
}
