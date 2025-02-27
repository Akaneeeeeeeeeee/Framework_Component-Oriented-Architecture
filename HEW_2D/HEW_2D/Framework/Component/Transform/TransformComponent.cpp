#include "TransformComponent.h"

// �Z�b�^�[
void TransformComponent::SetPosition(const Vector3& _Position) {
	m_Transform.m_Position = _Position;
}

void TransformComponent::SetRotation(const Vector3& _Rotation) {
	m_Transform.m_Rotation = _Rotation;
}

void TransformComponent::SetScale(const Vector3& _Scale) {
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

// �s��ϊ�
const Matrix&  TransformComponent::ConvertMatrix(void) const {
	XMMATRIX WorldPos, WorldRot, WorldScale;
	WorldPos = XMMatrixTranslation(m_Transform.m_Position.x, m_Transform.m_Position.y, m_Transform.m_Position.z);			// ���W�������[���h�s���
	WorldRot = XMMatrixRotationRollPitchYaw(m_Transform.m_Rotation.x, m_Transform.m_Rotation.y, m_Transform.m_Rotation.z);	// �p�x�����[���h�s���
	WorldScale = XMMatrixScaling(m_Transform.m_Scale.x, m_Transform.m_Scale.y, m_Transform.m_Scale.z);						// �X�P�[���i�傫���j�����[���h�s���
	return WorldPos * WorldRot * WorldScale;
	// TODO:1105�����܂ŁI�����[���h�s��ւ̕ϊ�������������

}

