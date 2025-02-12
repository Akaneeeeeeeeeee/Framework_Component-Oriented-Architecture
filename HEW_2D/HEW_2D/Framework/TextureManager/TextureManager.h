#pragma once
#include "../../Game/EntryPoint/main.h"
#include "../Singleton_Template/Singleton_Template.h"
#include "../../Framework/WICTextureLoader/WICTextureLoader.h"

using namespace Microsoft::WRL;

/**
 * @brief �摜�Ǘ����邽�߂̃��x��
*/
enum class TextureID
{
	PLAYER = 0,
	ENEMY,
	BOSS,
	UI_ITEM,
	GAMEBACK,
	TITLEBACK,
	RESULTBACK,

	ID_MAX
};


/**
 * @brief �Q�[���Ɏg����e�N�X�`�����ꊇ�Ǘ�����N���X
 * 
 * �t�@�C���p�X�Ɖ摜�f�[�^��texture2d�Ɏ������āA�����~�b�v�}�b�v�Ƃ��g���悤��texture2d�͔z��ɂ��Ă����B
 * �摜�̓��x��(�����瑤�Œ�`)���g���ĊǗ�����
 * 
 * ����������ID�ɕR�Â����t�@�C���p�X����texture2d�ɉ摜���������Ă���
 * ��SpriteRenderer�ɉ摜���𑗂肽������ComPtr<SRV>���擾���ēn��
*/
class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager();
	~TextureManager();

	void Init(void);
	void Uninit(void);

	//void LoadTextures()

	ComPtr<ID3D11ShaderResourceView> GetSRV(TextureID _ID);

private:
	// �~�b�v�}�b�v�Ȃǂ̂��Ƃ��l��(�P��Texture2D�ɑ΂��ĂP��SRV���K�v)�ATexture2D��SRV���ꂼ���map������Ă���
	// Texture2D�Ǘ��pmap
	std::unordered_map<TextureID, std::vector<ComPtr<ID3D11Texture2D>>> m_Textures;

	// SRV�Ǘ��pmap
	std::unordered_map<TextureID, std::vector<ComPtr<ID3D11ShaderResourceView>>> m_SRVs;
};

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}