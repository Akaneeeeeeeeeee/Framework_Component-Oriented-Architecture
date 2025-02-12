#include "TextureManager.h"


/**
 * @brief ������
 * �����őS�Ẳ摜��ǂݍ����Texture2D��SRV���쐬�A�ێ����Ă���
*/
void TextureManager::Init(void)
{
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
		// 
		HRESULT hr = DirectX::CreateWICTextureFromFileEx(D3d11.GetDevice(), D3d11.GetDeviceContext(), tex.second, 0, D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
		if (FAILED(hr))
		{
			MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
			return;
		}
		m_Textures.emplace(tex.first, tex.second);
	}

}

/**
 * @brief �摜��SRV���擾����֐�
 * @param _ID �e�N�X�`���Ǘ�ID
 * @return ID�Ŏw�肵���e�N�X�`����SRV
*/
ComPtr<ID3D11ShaderResourceView> TextureManager::GetSRV(TextureID _ID)
{

}

/**
 * @brief �I��
 * �e�R���e�i�ɕێ�����Ă���摜�����N���A
*/
void TextureManager::Uninit(void)
{
	m_Textures.clear();
	m_SRVs.clear();
}
