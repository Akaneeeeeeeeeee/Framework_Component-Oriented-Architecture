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
	// �����V�~�����[�V�������Ȃ��ꍇ�̓X�L�b�v
	if (IsKinematic)
	{ 
		// �����I�ɑ��x�����Z�b�g���Ă���
		m_Velocity = Vector3::Zero;
		return;
	}

	//---------------------------------------
	//			���̂ɂ�����͂̌v�Z
	//---------------------------------------
	// force �� �d�͂ɂ��́iF = m * g�j �����Z����
	// force �� ���̃t���[���̉����x�v�Z�Ɏg��

	// ����deltatime�g��Ȃ��̂Ŗ��t���[���F�X����������K�v���聨force�𖈃t���[�����Z�b�g����(���x��velocity�ɕێ�����Ă�̂Ŗ��Ȃ�)

	// �n���ł͏d�͉͂������ɂ�����̂�y�����ɉ��Z����
	m_Force.y += m_Mass * m_GravityScale;

	// �����x�����߂�
	// �j���[�g���̉^�������� F = m * a ���g���ĉ����x a ���v�Z
	// a = F(��) / m(����) �Ȃ̂ŁA���� m ���傫���قǉ������ɂ���

	// �O�����Z�q					������			�^�̏ꍇ				�U�̏ꍇ
	Vector3 acceleration = (m_Mass > 0) ? (m_Force / m_Mass) : Vector3::Zero;

	// ���x�̍X�V
	// ���x v �ɏ]���ăI�u�W�F�N�g���ړ�
	// p = p + v * dt�i�ϕ��j��deltatime�͎g��Ȃ�(FPS���Œ肳��Ă��邽��)
	// �ʒu p ���X�V����邱�ƂŁA�I�u�W�F�N�g������
	m_Velocity += acceleration;

	// �͂̃��Z�b�g(�����܂łɌĂ�addforce��force����ԍŌ�̂��̂ŏ㏑�����Ȃ����߂ɂ����ň�񂾂����Z�b�g����)
	m_Force = Vector3::Zero;

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
void RigidBody2D::AddForce(Vector3 _force, ForceMode2D _mode = ForceMode2D::Force)
{
	// �͂̉������ɂ���ď�����ς���
	switch (_mode)
	{
	// Force�̏ꍇ�A���킶��������铮���ɂȂ邽�߁A���t���[���Ăё�����K�v�����邩�璍��!
	case ForceMode2D::Force:
		m_Force += _force;		// �͂����Z
		break;
	//case ForceMode2D::Acceleration:
	//	Vector3 acceleration = _force;  // ���ʂ��l�����Ȃ�
	//	m_Velocity += acceleration;
		break;
	// ��t���[���Ŕ����I�ɉ���
	case ForceMode2D::Impulse:
		m_Velocity += _force / m_Mass;	// ���x�ɒ��ډe��
		break;
	// ���x�𒼂ŕύX
	case ForceMode2D::VelocityChange:
		m_Velocity = _force;
		break;
	default:
		break;
	}
}
