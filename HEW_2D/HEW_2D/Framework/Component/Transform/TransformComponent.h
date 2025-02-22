#pragma once
#include "Transform.h"
#include "../IComponent/IComponent.h"

/// <summary>
/// Transformの各数値の行列変換はTransform側で行い、TransformComponent側では各数値の変更（更新）だけを行う
/// </summary>

class TransformComponent :public IComponent
{
public:
	TransformComponent(Object* _Owner) :IComponent(_Owner) {};

	~TransformComponent(){}

	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

	void SetPosition(Vector3& const _Position);	// 座標設定
	void SetRotation(Vector3& const _Rotation);	// 角度設定
	void SetScale(Vector3& const _Scale);			// 大きさ設定
	const Vector3& GetPosition(void);
	const Vector3& GetRotation(void);
	const Vector3& GetScale(void);
	const Matrix& ConvertMatrix(void) const;		// Transformの各値をかけ合わせてワールド行列に変換

private:
	Transform m_Transform;
};
