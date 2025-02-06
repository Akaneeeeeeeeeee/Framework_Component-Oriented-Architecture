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
	//---------------------------------------
	//			���̂ɂ�����͂̌v�Z
	//---------------------------------------
	// force �� �d�͂ɂ��́iF = m * g�j �����Z����
	// force �� ���̃t���[���̉����x�v�Z�Ɏg��

	// �n���ł͏d�͉͂������ɂ�����̂�y�����ɉ��Z����
	m_Force.y += m_Mass * m_GravityScale;

	// �����x�����߂�
	// �j���[�g���̉^�������� F = m * a ���g���ĉ����x a ���v�Z
	// a = F(��) / m(����) �Ȃ̂ŁA���� m ���傫���قǉ������ɂ���
	Vector3 acceleration = m_Force / m_Mass;

	// ���x�̍X�V
	// ���x v �ɏ]���ăI�u�W�F�N�g���ړ�
	// p = p + v * dt�i�ϕ��j��deltatime�͎g��Ȃ�(FPS���Œ肳��Ă��邽��)
	// �ʒu p ���X�V����邱�ƂŁA�I�u�W�F�N�g������
	m_Velocity += acceleration;

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
