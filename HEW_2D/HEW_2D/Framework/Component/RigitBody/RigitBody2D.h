#pragma once
#include "../IComponent/IComponent.h"

using namespace SimpleMath;

/**
 * @brief 物理演算
 * 
 * このコンポーネントを取りつけていても当たり判定を検知しない設定に変更できるようにしたい
 * 
 * 重力、摩擦などが必要
 * 
 * 
 * 2. 最終的なコードのイメージ
C++ で RigidBody::Update(float deltaTime) を実装するなら、次のような形になります。

cpp
コピーする
編集する
void RigidBody::Update(float deltaTime) {
    // 1. 力の適用（例: 重力）
    force += mass * gravity;

    // 2. 加速度を求める
    Vector3 acceleration = force / mass;

    // 3. 速度を更新
    velocity += acceleration * deltaTime;

    // 4. 位置を更新
    position += velocity * deltaTime;

    // 5. 角速度の更新
    Vector3 angularAcceleration = torque / inertia;
    angularVelocity += angularAcceleration * deltaTime;
    rotation += angularVelocity * deltaTime;

    // 6. 衝突判定
    if (isColliding) {
        velocity = Reflect(velocity, collisionNormal) * restitution;
    }

    // 7. 力をリセット（毎フレームリセットして新しい力を受け付ける）
    force = Vector3(0, 0, 0);
    torque = Vector3(0, 0, 0);
}
3. まとめ
update の流れは次のようになります：

外力（重力・操作）を加える
加速度を求めて速度を更新
速度を使って座標を更新
角運動（回転）も計算
衝突処理
毎フレームの力をリセット
+α: 高精度な物理を目指すなら
オイラー積分の代わりにVerlet積分やRunge-Kutta法を使う
衝突検出をより正確に（AABB, OBB, GJKアルゴリズム）
剛体同士の摩擦や弾性衝突の計算
固定時間ステップの導入（物理更新は固定フレームで実施）
*/
class RigitBody2D :public IComponent
{
public:
	RigitBody2D();
	~RigitBody2D();

	void AddForce(Vector3);
	

private:
	bool m_DetectCollision;		// 衝突判定を有効にするか
	//float 
};

RigitBody2D::RigitBody2D()
{
}

RigitBody2D::~RigitBody2D()
{
}