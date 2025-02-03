#include "GameObject.h"

/**
 * @brief コンストラクタ
 * @param _D3d11 D3Dクラスの参照
*/
GameObject::GameObject(D3D11& _D3d11) :D3d11(_D3d11)
{
	// std::vectorを使うためコンストラクタで初期化
	vertices = {
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},	// 0番目の頂点座標
		{ 0.5f,  0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f },		// 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f },		// 2番目の頂点座標
		{ 0.5f, -0.5f, 0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f },		// 3番目の頂点座標
	};
	m_Direction = { 0.0f,0.0f,0.0f };
	m_Velocity = { 0.0f,0.0f,0.0f };
	m_AttachedOnomatopoeia = nullptr;
}

GameObject::~GameObject()
{
	Uninit();
}

void GameObject::Init(const wchar_t* imgname, int sx, int sy, bool _animation)
{
	// アニメーション有無を設定
	IsAnimation = _animation;

	//UV座標を設定
	m_Split.x = sx;
	m_Split.y = sy;
	vertices[1].u = 1.0f / m_Split.x;
	vertices[2].v = 1.0f / m_Split.y;
	vertices[3].u = 1.0f / m_Split.x;
	vertices[3].v = 1.0f / m_Split.y;


	// 頂点バッファを作成する
	// ※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = sizeof(vertices);	// 確保するバッファサイズを指定（vectorなので注意）
	bufferDesc.ByteWidth = static_cast<UINT>(vertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertices.data();	// VRAMに送るデータを指定（vectorなので注意）
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = D3d11.GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);

	// テクスチャ読み込み
//	hr = DirectX::CreateWICTextureFromFile(Device, imgname, NULL, &m_pTextureView);
	hr = DirectX::CreateWICTextureFromFileEx(D3d11.GetDevice(), D3d11.GetDeviceContext(), imgname, 0, D3D11_USAGE_DEFAULT,
		D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
		return;
	}
}


/**
 * @brief オブジェクトの更新 
*/
void GameObject::Update(void)
{
	// 物理挙動をここに書く
	// 毎フレームの挙動
	// ・重力加速度を下方向に加える
	// ・方向ベクトルの向きに


	// 速度分だけ移動
	Vector3 newpos = transform.GetPosition();
	newpos+= m_Direction * m_Velocity;
	transform.SetPosition(newpos);

	// 摩擦や空気抵抗を考慮（加速度の減少）
	m_Velocity *= 0.95f;		// 毎フレーム5% 減衰
	
	// 一定以下なら完全停止
	if (fabs(m_Velocity.x) < 0.01f) {
		m_Velocity.x = 0.0f;
	}
	if (fabs(m_Velocity.y) < 0.01f)
	{
		m_Velocity.y = 0.0f;
	}

}


void GameObject::Draw(void)
{
	//頂点バッファを設定
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	D3d11.GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	// テクスチャをピクセルシェーダーに渡す
	D3d11.GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTextureView);

	//定数バッファを更新

	// プロジェクション変換行列を作成
	cb.matrixProj = DirectX::XMMatrixOrthographicLH( SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	// ワールド変換行列の作成
	// →オブジェクトの位置・大きさ・向きを指定
	cb.matrixWorld = DirectX::XMMatrixScaling(transform.GetScale().x, transform.GetScale().y, transform.GetScale().z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(transform.GetRotation().z * 3.14f / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	// UVアニメーションの行列作成
	float u = (float)m_Number.x / m_Split.x;
	float v = (float)m_Number.y / m_Split.y;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	//頂点カラーのデータを作成
	cb.color = m_Color;

	// 行列をシェーダーに渡す
	D3d11.GetDeviceContext()->UpdateSubresource(D3d11.GetConstantBuffer(), 0, NULL, &cb, 0, 0);

	D3d11.GetDeviceContext()->Draw(4, 0); // 描画命令
}

void GameObject::Uninit()
{
	//開放処理
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTextureView);
}

void GameObject::SetPosition(Vector3 _Pos) 
{
	//座標をセットする
	transform.SetPosition(_Pos);
}

void GameObject::SetScale(Vector3 _Size) 
{
	//大きさをセットする
	transform.SetScale(_Size);
}

void GameObject::SetRotation(Vector3 _Rot) 
{
	//角度をセットする
	transform.SetRotation(_Rot);
}

void GameObject::SetColor(Color _Color)
{
	//色をセットする
	m_Color.x = _Color.x;
	m_Color.y = _Color.y;
	m_Color.z = _Color.z;
	m_Color.w = _Color.w;
}

void GameObject::SetUV(Int2 _UV)
{
	m_Number.x = _UV.x;
	m_Number.y = _UV.y;
}

void GameObject::SetParent(const std::weak_ptr<GameObject> _Parent)
{
	// 親オブジェクトを設定
	m_pParent = _Parent;
}

void GameObject::SetChild(const std::shared_ptr<GameObject> _Child)
{
	// 子オブジェクトを追加
	m_pChildren.push_back(_Child);
}

void GameObject::AddForce(Vector3 _Vel)
{
	m_Velocity = _Vel;
}

void GameObject::SetDirection(Vector3 _Dir)
{
	m_Direction = _Dir;
}

void GameObject::SetOnGround(bool _flg) {
	OnGround = _flg;
}

void GameObject::SetIsDelete(bool _flg)
{
	IsDelete = _flg;
}

/**
 * @brief アニメーション遷移関数
 * ここでは通常のアニメーションのみを定義し、各派生クラスで各々のアニメーション処理を定義する
*/
void GameObject::Animation(STATE m_State,std::weak_ptr<GameObject> _efect)
{
	
	const float uvUpdateInterval = 0.1f; // 0.1秒ごとに更新（10FPS相当）
	
	// 経過時間
	static float elapsedTime = 0.0f;
	


		// ここにアニメーション遷移処理を書く
		switch (m_State)
		{
		case EFECT:

			elapsedTime += 0.03;

			// 指定した時間が経過したらUVを更新
 			if (elapsedTime >= uvUpdateInterval) {
				elapsedTime = 0.0f; // タイマーをリセット

				Int2 efect_UV = _efect.lock()->GetUV();

				if (efect_UV.x < 8) {
					efect_UV.x++;
				}
				else {
					efect_UV.x = 0;
					efect_UV.y = (efect_UV.y == 0) ? 1 : 0;
				}

				_efect.lock()->SetUV(efect_UV);
			}

			break;
	//	case Jump:
	//		break;
		default:
			break;
		}
	}
Vector3 GameObject::GetPosition(void)
{
	//座標をゲット
	return transform.GetPosition();
}
  
Vector3 GameObject::GetScale(void)
{
	//大きさをゲット
	return transform.GetScale();
}

Vector3 GameObject::GetRotation(void)
{
	//角度をゲット
	return transform.GetRotation();
}

Color GameObject::GetColor(void)
{
	//色をゲット
	return m_Color;
}

Int2 GameObject::GetUV(void)
{
	//UV座標をゲット
	return m_Number;
}
            
Vector3 GameObject::GetVelocity(void)
{
	return m_Velocity;
}

Vector3 GameObject::GetDirection(void)
{
	return m_Direction;
}
