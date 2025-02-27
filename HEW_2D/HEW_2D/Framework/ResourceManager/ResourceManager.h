#pragma once
#include "../../Game/EntryPoint/main.h"
#include "../Singleton_Template/Singleton_Template.h"
#include "../../Framework/WICTextureLoader/WICTextureLoader.h"
#include "../Component/Renderer/Shader/Shader.h"

using namespace Microsoft::WRL;

/**
 * @brief �摜�Ǘ����邽�߂̃��x��
*/
enum class TextureID
{
	PLAYER = 0,
	ENEMY,
	BOSS,
	UI,
	UI_ITEM,
	GAMEBACK,
	BUTTON_START,
	BUTTON_END,
	CURSOR_CHARACTER,
	TITLELOGO,
	TITLEBACK,
	RESULTBACK,

	ID_MAX
};

enum class ShaderID {
	SHADER_NORMAL
};


/**
 * @brief �Q�[���Ɏg���郊�\�[�X(�e�N�X�`���A�V�F�[�_�[�A�T�E���h�Ȃ�)���ꊇ�Ǘ�����N���X
 * 
 * �t�@�C���p�X�Ɖ摜�f�[�^��texture2d�Ɏ������āA�����~�b�v�}�b�v�Ƃ��g���悤��texture2d�͔z��ɂ��Ă����B
 * �摜�̓��x��(�����瑤�Œ�`)���g���ĊǗ�����
 * 
 * ����������ID�ɕR�Â����t�@�C���p�X����texture2d�ɉ摜���������Ă���
 * ��SpriteRenderer�ɉ摜���𑗂肽������ComPtr<SRV>���擾���ēn��
 * 
 * �V�F�[�_�[��������map�ɓo�^���ĊǗ�����
 * 
*/
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);

	void LoadShader(ShaderID _ID, const std::string& vsFile, const std::string& vsEntryPoint,
		const std::string& psFile, const std::string& psEntryPoint, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);

	//! �e�N�X�`����SRV�̃Q�b�^�[
	ComPtr<ID3D11ShaderResourceView> GetSRV(const TextureID& _ID);

	// �V�F�[�_�[�̃Q�b�^�[(���|�C���^��Ԃ�)
	Shader* GetShader(const ShaderID& _ID);


private:
	// �~�b�v�}�b�v�Ȃǂ̂��Ƃ��l��(�P��Texture2D�ɑ΂��ĂP��SRV���K�v)�ATexture2D��SRV���ꂼ���map������Ă���
	// Texture2D�Ǘ��pmap
	//std::unordered_map<TextureID, std::vector<ComPtr<ID3D11Texture2D>>> m_Textures;

	// SRV�Ǘ��pmap
	//std::unordered_map<TextureID, std::vector<ComPtr<ID3D11ShaderResourceView>>> m_SRVs;		// vector�̓~�b�v�}�b�v�̂��߂Ɏg��������͕K�v�Ȃ��̂Ŏg��Ȃ�
	std::unordered_map<TextureID, ComPtr<ID3D11ShaderResourceView>> m_SRVs;

	// �V�F�[�_�[�Ǘ��pmap
	std::unordered_map<ShaderID, std::unique_ptr<Shader>> m_Shaders;

	// �T�E���h�Ǘ�map
};
