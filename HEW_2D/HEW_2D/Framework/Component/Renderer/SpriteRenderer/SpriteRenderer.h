#pragma once
#include "../../IComponent/IComponent.h"
#include "../../../D3D11/D3D11.h"

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

/**
 * @brief 画像描画コンポーネント
 * 
 * 頂点座標
 * 頂点情報
 * インデックスバッファ
 * 画像情報
*/
class SpriteRenderer :public IComponent
{
public:
	SpriteRenderer() = delete;
	SpriteRenderer(GameObject* _Owner) :IComponent(_Owner) {};
	~SpriteRenderer() {};

private:
	//! 頂点データ
	//! このゲームでは擬音を吸い込むことがあるため頂点を可変にしておく
	std::vector<Vertex> m_Vertices;

	// 色
	Color m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 頂点バッファ
	ComPtr<ID3D11Buffer> m_pVertexBuffer;

	// インデックスバッファ
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	// テクスチャ用変数
	ComPtr<ID3D11ShaderResourceView> m_pTextureView;

	//テクスチャが縦横に何分割されているか
	XMINT2 m_Split = { 1,1 };

	//左上から何段目を切り抜いて表示するか
	XMINT2 m_Number = { 0,0 };
};

