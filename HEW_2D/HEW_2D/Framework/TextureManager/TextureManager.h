#pragma once
#include "../../Game/EntryPoint/main.h"
#include "../Singleton_Template/Singleton_Template.h"

/**
 * @brief ゲームに使われるテクスチャを一括管理するクラス
 * 
 * ファイルパスと画像データをtexture2dに持たせて、もしミップマップとか使うようにtexture2dは配列にして
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