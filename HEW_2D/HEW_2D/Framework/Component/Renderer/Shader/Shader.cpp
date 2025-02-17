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
#include "../../../DX11Helper/dx11helper.h"


/**
 * @brief ������
 * @return �������̌���
 * 
 * �����ŃV�F�[�_�[���쐬
*/
void Shader::Init(const std::string& vsFile, const std::string& vsEntryPoint, 
	const std::string& psFile, const std::string& psEntryPoint, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements)
{
	bool sts;

	//// �C���v�b�g���C�A�E�g�쐬
	//// POSITION �� XMFLOAT3 ������ DXGI_FORMAT_R32G32B32_FLOAT
	//// TEXCOORD �� XMFLOAT2 ������ DXGI_FORMAT_R32G32_FLOAT
	//// 0, 12 �̕����ŁA���ꂼ��̃f�[�^���o�b�t�@���łǂ��ɂ��邩���w�肵�Ă���
	//D3D11_INPUT_ELEMENT_DESC layout[]
	//{
	//	// �ʒu���W������Ƃ������Ƃ�`����
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	// �F��񂪂���Ƃ������Ƃ�`����
	//	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	// UV���W
	//	{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};


	// �e�V�F�[�_�[���R���p�C�����č쐬(�o�[�W�������͌��܂��Ă�̂ň����͎g��Ȃ�(����_5.0�Ƃ�))
	// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	sts = CreateVertexShader(D3D11::GetInstance().GetDevice(), vsFile.c_str(), vsEntryPoint.c_str(),
		"vs_5_0", layout, numElements, &m_pVertexShader, &m_pVertexLayout);
	if (!sts) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return;
	}

	// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	sts = CreatePixelShader(D3D11::GetInstance().GetDevice(), psFile.c_str(), psEntryPoint.c_str(), "ps_5_0", &m_pPixelShader);
	if (!sts) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return;
	}

}


void Shader::Update(void)
{
	// �`��̂��߂̏���GPU�ɓn��
	auto devicecontext = D3D11::GetInstance().GetDeviceContext();
	devicecontext->IASetInputLayout(m_pVertexLayout.Get());
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->VSSetShader(m_pVertexShader.Get(), NULL, 0);		// �����ŕ`��Ɏg���V�F�[�_�t�@�C����K�p���Ă�
	devicecontext->PSSetShader(m_pPixelShader.Get(), NULL, 0);
}


void Shader::Uninit(void)
{

}


ID3D11VertexShader* Shader::GetVertexShader(void)
{
	return m_pVertexShader.Get();
}

ID3D11PixelShader* Shader::GetPixelShader(void)
{
	return m_pPixelShader.Get();
}
