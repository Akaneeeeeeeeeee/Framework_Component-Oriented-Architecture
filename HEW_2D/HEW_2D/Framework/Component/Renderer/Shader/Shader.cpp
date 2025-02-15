#include "Shader.h"
#include "../../../../Game/EntryPoint/main.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <locale.h>
#include <atltypes.h> // CRect���g�����߂̃w�b�_�[�t�@�C��
#include <io.h>
#include <stdio.h>
#include <string.h>
#include "../../../D3D11/D3D11.h"



void Shader::Init(void)
{
	HRESULT hr;

	// �C���v�b�g���C�A�E�g�쐬
	// POSITION �� XMFLOAT3 ������ DXGI_FORMAT_R32G32B32_FLOAT
	// TEXCOORD �� XMFLOAT2 ������ DXGI_FORMAT_R32G32_FLOAT
	// 0, 12 �̕����ŁA���ꂼ��̃f�[�^���o�b�t�@���łǂ��ɂ��邩���w�肵�Ă���
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// �ʒu���W������Ƃ������Ƃ�`����
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// �F��񂪂���Ƃ������Ƃ�`����
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV���W
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	hr = D3D11::CreateVertexShader(m_pDevice.Get(), "Shader/VertexShader.hlsl", "vs_main", "vs_5_0",
		layout, numElements, &m_pVertexShader, &m_pInputLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	hr = CreatePixelShader(m_pDevice.Get(), "Shader/PixelShader.hlsl", "ps_main", "ps_5_0", &m_pPixelShader);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return E_FAIL;
	}
}
