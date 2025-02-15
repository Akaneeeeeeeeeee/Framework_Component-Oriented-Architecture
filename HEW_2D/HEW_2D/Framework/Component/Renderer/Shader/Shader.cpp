#include "Shader.h"
#include "../../../../Game/EntryPoint/main.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <atltypes.h> // CRectを使うためのヘッダーファイル
#include <io.h>
#include <stdio.h>
#include <string.h>
#include "../../../D3D11/D3D11.h"



void Shader::Init(void)
{
	HRESULT hr;

	// インプットレイアウト作成
	// POSITION → XMFLOAT3 だから DXGI_FORMAT_R32G32B32_FLOAT
	// TEXCOORD → XMFLOAT2 だから DXGI_FORMAT_R32G32_FLOAT
	// 0, 12 の部分で、それぞれのデータがバッファ内でどこにあるかを指定している
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// 位置座標があるということを伝える
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 色情報があるということを伝える
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV座標
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	hr = D3D11::CreateVertexShader(m_pDevice.Get(), "Shader/VertexShader.hlsl", "vs_main", "vs_5_0",
		layout, numElements, &m_pVertexShader, &m_pInputLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return E_FAIL;
	}

	// ピクセルシェーダーオブジェクトを生成
	hr = CreatePixelShader(m_pDevice.Get(), "Shader/PixelShader.hlsl", "ps_main", "ps_5_0", &m_pPixelShader);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return E_FAIL;
	}
}
