#pragma once
#include "Transform.h"
#include "../IComponent/IComponent.h"

/// <summary>
/// Transform�̊e���l�̍s��ϊ���Transform���ōs���ATransformComponent���ł͊e���l�̕ύX�i�X�V�j�������s��
/// </summary>

class TransformComponent :public IComponent
{
public:
	TransformComponent(Object* _Owner) :IComponent(_Owner) {};

	~TransformComponent(){}

	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

	void SetPosition(Vector3& const _Position);	// ���W�ݒ�
	void SetRotation(Vector3& const _Rotation);	// �p�x�ݒ�
	void SetScale(Vector3& const _Scale);			// �傫���ݒ�
	const Vector3& GetPosition(void);
	const Vector3& GetRotation(void);
	const Vector3& GetScale(void);
	const Matrix& ConvertMatrix(void) const;		// Transform�̊e�l���������킹�ă��[���h�s��ɕϊ�

private:
	Transform m_Transform;
};
