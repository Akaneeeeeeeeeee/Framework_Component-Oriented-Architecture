#pragma once
#include "../../Game/EntryPoint/main.h"
#include "../Singleton_Template/Singleton_Template.h"

/**
 * @brief �Q�[���Ɏg����e�N�X�`�����ꊇ�Ǘ�����N���X
 * 
 * �t�@�C���p�X�Ɖ摜�f�[�^��texture2d�Ɏ������āA�����~�b�v�}�b�v�Ƃ��g���悤��texture2d�͔z��ɂ���
*/
class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager();
	~TextureManager();

private:
	//std::unordered_map<std::string>
};

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}