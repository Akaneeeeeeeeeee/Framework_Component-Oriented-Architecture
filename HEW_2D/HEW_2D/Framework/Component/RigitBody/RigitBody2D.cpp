#include "RigitBody2D.h"

/**
 * @brief ������
 * @param  
*/
void RigidBody2D::Init(void)
{

}

/**
 * @brief �X�V
 * 
 * �����v�Z�̏��Ԃ́A
 * �P�F��
 * �Q�F�����x
 * �R�F���x
 * �S�F�ʒu
 * �Ȃ̂ł��̏��ԂŌv�Z����
 * 
 * TODO:2025/0206 �������Z�̎d�g�݂𗝉�����
 * 
*/
void RigidBody2D::Update(void)
{
	// �͂̌v�Z
	// force �� �d�͂ɂ��́iF = m * g�j �����Z����
	// force �� ���̃t���[���̉����x�v�Z�Ɏg��
	m_Force += m_Mass * m_GravityScale;

	// �����x�����߂�
	Vector3 acceleration = m_Force / m_Mass;
}

/**
 * @brief �I��
 * @param  
*/
void RigidBody2D::Uninit(void)
{
	// �A�^�b�`����Ă���I�u�W�F�N�g�̃|�C���^��nullptr��
	m_pOwner = nullptr;
}

/**
 * @brief �͂�������֐�
 * @param _force �������
 * @param _mode �͂̉�����(�f�t�H���g��Force)
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
