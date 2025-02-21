#include "SpriteRenderer.h"
#include "../../../ResourceManager/ResourceManager.h"


void SpriteRenderer::Init(void)
{
	// 頂点情報初期化
	m_Vertices = {
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },	// 0番目の頂点座標
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },	// 1番目の頂点座標
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 2番目の頂点座標
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },	// 3番目の頂点座標
	};


	// 頂点バッファを作成する
	// ※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = sizeof(vertices);	// 確保するバッファサイズを指定（vectorなので注意）
	bufferDesc.ByteWidth = static_cast<UINT>(m_Vertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = m_Vertices.data();	// VRAMに送るデータを指定（vectorなので注意）
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = D3D11::GetInstance().GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}


void SpriteRenderer::Update(void)
{
	
}


void SpriteRenderer::Uninit(void)
{
	m_pShader.reset();
}


/**
 * @brief テクスチャ設定
 * @param _ID 登録されているID
 * @param _split 画像分割数
*/
void SpriteRenderer::SetTexture(TextureID _ID, XMINT2 _split)
{
	// リソースマネージャに登録されているIDからSRVを取得して登録
	this->m_pTextureView = ResourceManager::GetInstance().GetSRV(_ID);
	// 分割数設定
	this->m_Split = _split;
	m_Vertices[1].u = 1.0f / m_Split.x;
	m_Vertices[2].v = 1.0f / m_Split.y;
	m_Vertices[3].u = 1.0f / m_Split.x;
	m_Vertices[3].v = 1.0f / m_Split.y;
}

/**
 * @brief シェーダー設定
 * @param _shader リソースマネージャから持ってきたシェーダーのshared_ptr
*/
void SpriteRenderer::SetShader(std::shared_ptr<Shader> _shader)
{
	this->m_pShader = _shader;
}
