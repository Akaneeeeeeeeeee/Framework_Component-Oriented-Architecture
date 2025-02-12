#pragma once
#include "../../Game/EntryPoint/main.h"
#include "../Singleton_Template/Singleton_Template.h"
#include "../../Framework/WICTextureLoader/WICTextureLoader.h"

using namespace Microsoft::WRL;

/**
 * @brief 画像管理するためのラベル
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
 * @brief ゲームに使われるテクスチャを一括管理するクラス
 * 
 * ファイルパスと画像データをtexture2dに持たせて、もしミップマップとか使うようにtexture2dは配列にしておく。
 * 画像はラベル(こちら側で定義)を使って管理する
 * 
 * 初期化時にIDに紐づけたファイルパスからtexture2dに画像情報を代入しておく
 * →SpriteRendererに画像情報を送りたい時にComPtr<SRV>を取得して渡す
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
	// ミップマップなどのことを考え(１つのTexture2Dに対して１つのSRVが必要)、Texture2DとSRVそれぞれのmapを作っておく
	// Texture2D管理用map
	std::unordered_map<TextureID, std::vector<ComPtr<ID3D11Texture2D>>> m_Textures;

	// SRV管理用map
	std::unordered_map<TextureID, std::vector<ComPtr<ID3D11ShaderResourceView>>> m_SRVs;
};

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}