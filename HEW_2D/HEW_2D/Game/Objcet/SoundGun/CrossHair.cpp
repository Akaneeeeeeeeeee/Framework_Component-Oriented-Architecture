#include "CrossHair.h"


CrossHair::CrossHair(const UINT& _ID, const Tag& _tag, const std::string& _name) : Object(_ID, _tag, _name) {
	MoveLeft = false;
	MoveRight = false;
	MoveUp = false;
	MoveDown = false;
	GetComponent<RigidBody2D>()->AddForce(Vector3(10.0f, 0.0f, 0.0f), ForceMode2D::VelocityChange);	// �N���X�w�A�̈ړ����x
}

/**
 * @brief �X�V
*/
void CrossHair::Update(void)
{
	// ���W�ݒ�p�ϐ�
	Vector3 newpos = transform.GetPosition();

	// ���ړ�
	if (MoveLeft)
	{
		newpos.x -= m_Velocity.x;
	}
	// �E�ړ�
	if (MoveRight)
	{
		newpos.x += m_Velocity.x;
	}
	// ��ړ�
	if (MoveUp)
	{
		newpos.y += m_Velocity.y;
	}
	// ���ړ�
	if (MoveDown)
	{
		newpos.y -= m_Velocity.y;
	}
	transform.SetPosition(newpos);
}
