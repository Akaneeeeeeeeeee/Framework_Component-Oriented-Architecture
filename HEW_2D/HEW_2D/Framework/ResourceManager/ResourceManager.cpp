#include "ResourceManager.h"
#include "../DX11Helper/dx11helper.h"
#include <array>


/**
 * @brief ������
 * �����őS�Ẳ摜��ǂݍ����Texture2D��SRV���쐬�A�ێ����Ă���
*/
HRESULT ResourceManager::Init(void)
{
	/////////////////////////////////////////////////
	///				�e�N�X�`���ǂݍ���
	/////////////////////////////////////////////////

	//! �e�N�X�`��ID�ɑΉ������t�@�C���p�X��ݒ�
	std::unordered_map<TextureID, std::wstring> Filepath_Texture = {
		{TextureID::PLAYER, L"Game/Asset/Character/Player.png"},
		{TextureID::ENEMY, L"Game/Asset/GameObject/Slime.png"},
		{TextureID::TITLEBACK, L"Game/Asset/UI/TitleLogo.png"},
		{TextureID::GAMEBACK, L"Game/Asset/BackGround/TitleBack.png"}
	};


	//! �ݒ肵���t�@�C���p�X�ɂ���摜��ǂݍ����Texture2D��SRV���쐬�A�L���b�V������
	//! D3d11�̈����ǂ����悤�H
	//! �ˑ��������H��������D3D11�N���X�𑶍݂����Ă����ׂ����ǂ����B�؂蕪���ĕʃN���X�ɂ��Ă��܂����ق��������̂��H
	for (auto& tex : Filepath_Texture)
	{
		// �e�N�X�`���̃p�X��ǂݍ���
		HRESULT hr = CreateWICTextureFromFileEx(D3D11::GetInstance().GetDevice(), D3D11::GetInstance().GetDeviceContext(), tex.second.c_str(), 0, D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, m_SRVs[tex.first].GetAddressOf());
		if (FAILED(hr))
		{
			MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
			return hr;
		}
		// �쐬����SRV��map�ɓo�^
		m_SRVs.emplace(tex);
	}

	//////////////////////////////////////
	///			�V�F�[�_�[�ǂݍ���
	//////////////////////////////////////
	/// �V�F�[�_�[��map�i�V�F�[�_�[ID,�V�F�[�_�[�t�@�C���p�X�j����遨����map�ɓo�^����Ă���
	std::unordered_map<ShaderID, std::array<std::string, 4>> Filepath_VS_PS = {
		{ShaderID::SHADER_NORMAL, {"Shader/VertexShader.hlsl", "vs_main", "Shader/PixelShader.hlsl", "ps_main"}}
	};

	HRESULT hr;

	// �C���v�b�g���C�A�E�g�쐬(�V�F�[�_�[�̎�ނ�������ꍇ�A������InputLayout���ʂŋL�q)
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
	UINT numElements = ARRAYSIZE(layout);

	// �V�F�[�_�[�̍쐬�A�ǂݍ���
	this->LoadShader(ShaderID::SHADER_NORMAL,
		Filepath_VS_PS[ShaderID::SHADER_NORMAL][0],
		Filepath_VS_PS[ShaderID::SHADER_NORMAL][1],
		Filepath_VS_PS[ShaderID::SHADER_NORMAL][2],
		Filepath_VS_PS[ShaderID::SHADER_NORMAL][3],
		layout, numElements
	);
}


void ResourceManager::Update(void)
{

}

/**
 * @brief �摜��SRV���擾����֐�
 * @param _ID �e�N�X�`���Ǘ�ID
 * @return ID�Ŏw�肵���e�N�X�`����SRV
*/
ComPtr<ID3D11ShaderResourceView> ResourceManager::GetSRV(const TextureID& _ID)
{
	// �w�肵���L�[��SRV��Ԃ�
	return m_SRVs[_ID];
}

/**
 * @brief �V�F�[�_�[�̃Q�b�^�[
 * @param _ID �V�F�[�_�[ID
 * @return �w�肳�ꂽ�V�F�[�_�[�̐��|�C���^
*/
Shader* ResourceManager::GetShader(const ShaderID& _ID)
{
	return m_Shaders[_ID].get();
}

/**
 * @brief �I��
 * �e�R���e�i�ɕێ�����Ă���摜�����N���A
*/
void ResourceManager::Uninit(void)
{
	m_SRVs.clear();
}


/**
 * @brief �V�F�[�_�[�쐬
 * @param _ID �V�F�[�_�[ID
 * @param vsFile ���_�V�F�[�_�[�t�@�C����
 * @param psFile �s�N�Z���V�F�[�_�[�t�@�C����
 * @param device D3D�̃f�o�C�X
 * @param layout InputLayout
 * @param numElements InputLayput�̔z�u�H�݂����Ȋ���
*/
void ResourceManager::LoadShader(ShaderID _ID, const std::string& vsFile, const std::string& vsEntryPoint,
	const std::string& psFile, const std::string& psEntryPoint, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements)
{
	// �V�F�[�_�[�p�ϐ��쐬
	auto shader = std::make_unique<Shader>();
	// �R���p�C���A����
	shader->Init(vsFile, vsEntryPoint, psFile, psEntryPoint, layout, numElements);
	// map�ɓo�^(���L�����ړ�)
	m_Shaders[_ID] = std::move(shader);
}
