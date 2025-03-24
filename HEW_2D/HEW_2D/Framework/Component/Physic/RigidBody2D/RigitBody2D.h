#pragma once
#include "../../IComponent/IComponent.h"

using namespace SimpleMath;

/**
 * @brief �͂̉�����
 * 
 * �Q�l�T�C�g
 * https://shibuya24.info/entry/unity-rigidbody-addforce#ForceMode%E3%80%8CForce%EF%BC%88%E3%83%95%E3%82%A9%E3%83%BC%E3%82%B9%EF%BC%89%E3%80%8D
 * https://rightcode.co.jp/blogs/25168
 * 
 * acceleration��velocitychange��2D�ɂ͑��݂��Ȃ�
 * ���Avelocitychange�͏����I�ɂ͑��x�𒼐ڏ��������Ă邾���Ȃ̂ł����ł͎������Ă��܂�
*/
enum class ForceMode2D {
    Force,              // ���ʂ��l�����Čp���I�ȗ͂�������(�f�t�H���g�͂���)
    // Acceleration,       // ���ʂ�"����"���ĉ����x��������
    Impulse,            // ���ʂ��l�����ďu�ԓI�ȗ͂�������
    VelocityChange      // ���ʂ�"����"���đ��x�𒼐ڕύX����
};

/**
 * @brief �������Z
 * 
 * ���̃R���|�[�l���g�������Ă��Ă������蔻������m���Ȃ��ݒ�ɕύX�ł���悤�ɂ�����
 * 
 * �d�́A���C�Ȃǂ��K�v
 * 
 * 
 * 2. �ŏI�I�ȃR�[�h�̃C���[�W
C++ �� RigidBody::Update(float deltaTime) ����������Ȃ�A���̂悤�Ȍ`�ɂȂ�܂��B

cpp
�R�s�[����
�ҏW����
void RigidBody::Update(float deltaTime) {
    // 1. �͂̓K�p�i��: �d�́j
    force += mass * gravity;

    // 2. �����x�����߂�
    Vector3 acceleration = force / mass;

    // 3. ���x���X�V
    velocity += acceleration * deltaTime;

    // 4. �ʒu���X�V
    position += velocity * deltaTime;

    // 5. �p���x�̍X�V
    Vector3 angularAcceleration = torque / inertia;
    angularVelocity += angularAcceleration * deltaTime;
    rotation += angularVelocity * deltaTime;

    // 6. �Փ˔���
    if (isColliding) {
        velocity = Reflect(velocity, collisionNormal) * restitution;
    }

    // 7. �͂����Z�b�g�i���t���[�����Z�b�g���ĐV�����͂��󂯕t����j
    force = Vector3(0, 0, 0);
    torque = Vector3(0, 0, 0);
}
3. �܂Ƃ�
update �̗���͎��̂悤�ɂȂ�܂��F

�O�́i�d�́E����j��������
�����x�����߂đ��x���X�V
���x���g���č��W���X�V
�p�^���i��]�j���v�Z
�Փˏ���
���t���[���̗͂����Z�b�g
+��: �����x�ȕ�����ڎw���Ȃ�
�I�C���[�ϕ��̑����Verlet�ϕ���Runge-Kutta�@���g��
�Փˌ��o����萳�m�ɁiAABB, OBB, GJK�A���S���Y���j
���̓��m�̖��C��e���Փ˂̌v�Z
�Œ莞�ԃX�e�b�v�̓����i�����X�V�͌Œ�t���[���Ŏ��{�j
*/
class RigidBody2D :public IComponent
{
public:
    RigidBody2D(Object* _owner) :IComponent(_owner)
    {
        m_Velocity = { 0.0f };
        m_Direction = { 0.0f };
        m_Force = { 0.0f };
        m_Mass = 1.0f;
        m_GravityScale = 0.98f;
        DetectCollision = true;
        UseGravity = true;
        IsKinematic = false;
    };
    ~RigidBody2D() {};


    //--------------------------------
    //        �I�[�o�[���C�h�֐�
    //--------------------------------
    void Init(void) override;
    void Update(void) override;
    void Uninit(void) override;


    //--------------------------------
    //          �I���W�i���֐�
    //--------------------------------
    
    // �͂�������
    void AddForce(Vector3 _force, ForceMode2D _mode);
	
private:
    // ���x(����͖��t���[���ω�����l)
    Vector3 m_Velocity;

    // �ړ��p�����x�N�g��(Transform.Rotaion�͉�]���������̂Ȃ̂ŕʕ�)
    Vector3 m_Direction;

    // ��
    Vector3 m_Force;

    // ����(�P�ʁFkg)
    float m_Mass;

    // �d��
    float m_GravityScale;
    
    // �Փ˔����L���ɂ��邩(�f�t�H���g�ł�ON)
	bool DetectCollision;

    // �d�͂̉e�����󂯂邩(�f�t�H���g�ł�ON)
    bool UseGravity;

    // ���������̗L��(�f�t�H���g��OFF(��������������))
    bool IsKinematic;

    // ��]�̉e�����󂯂邩
    //bool FreezeRotation;
};

