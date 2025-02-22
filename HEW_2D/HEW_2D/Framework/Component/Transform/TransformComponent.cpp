#include "TransformComponent.h"

// セッター
void TransformComponent::SetPosition(Vector3& const _Position) {
	m_Transform.m_Position = _Position;
}

void TransformComponent::SetRotation(Vector3& const _Rotation) {
	m_Transform.m_Rotation = _Rotation;
}

void TransformComponent::SetScale(Vector3& const _Scale) {
	m_Transform.m_Scale = _Scale;
}

const Vector3& TransformComponent::GetPosition(void) {
	return m_Transform.m_Position;
}

const Vector3& TransformComponent::GetRotation(void) {
	return m_Transform.m_Rotation;
}

const Vector3& TransformComponent::GetScale(void) {
	return m_Transform.m_Scale;
}

// 行列変換
const Matrix&  TransformComponent::ConvertMatrix(void) const {
	XMMATRIX WorldPos, WorldRot, WorldScale;
	WorldPos = XMMatrixTranslation(m_Transform.m_Position.x, m_Transform.m_Position.y, m_Transform.m_Position.z);			// 座標ををワールド行列へ
	WorldRot = XMMatrixRotationRollPitchYaw(m_Transform.m_Rotation.x, m_Transform.m_Rotation.y, m_Transform.m_Rotation.z);	// 角度をワールド行列へ
	WorldScale = XMMatrixScaling(m_Transform.m_Scale.x, m_Transform.m_Scale.y, m_Transform.m_Scale.z);						// スケール（大きさ）をワールド行列へ
	return WorldPos * WorldRot * WorldScale;
	// TODO:1105ここまで！→ワールド行列への変換を完成させる

}

