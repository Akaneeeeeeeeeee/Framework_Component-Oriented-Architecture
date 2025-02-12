#include "TextureManager.h"


/**
 * @brief 初期化
 * ここで全ての画像を読み込んでTexture2DとSRVを作成、保持しておく
*/
void TextureManager::Init(void)
{
	//! テクスチャIDに対応したファイルパスを設定
	std::unordered_map<TextureID, std::wstring> Filepath_Texture = {
		{TextureID::PLAYER, L"Game/Asset/Character/Player.png"},
		{TextureID::ENEMY, L"Game/Asset/GameObject/Slime.png"},
		{TextureID::TITLEBACK, L"Game/Asset/UI/TitleLogo.png"},
		{TextureID::GAMEBACK, L"Game/Asset/BackGround/TitleBack.png"}
	};

	//! 設定したファイルパスにある画像を読み込んでTexture2DとSRVを作成、キャッシュする
	//! D3d11の扱いどうしよう？
	//! 依存性注入？そもそもD3D11クラスを存在させておくべきかどうか。切り分けて別クラスにしてしまったほうがいいのか？
	for (auto& tex : Filepath_Texture)
	{
		// 
		HRESULT hr = DirectX::CreateWICTextureFromFileEx(D3d11.GetDevice(), D3d11.GetDeviceContext(), tex.second, 0, D3D11_USAGE_DEFAULT,
			D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &m_pTextureView);
		if (FAILED(hr))
		{
			MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー", MB_ICONERROR | MB_OK);
			return;
		}
		m_Textures.emplace(tex.first, tex.second);
	}

}

/**
 * @brief 画像のSRVを取得する関数
 * @param _ID テクスチャ管理ID
 * @return IDで指定したテクスチャのSRV
*/
ComPtr<ID3D11ShaderResourceView> TextureManager::GetSRV(TextureID _ID)
{

}

/**
 * @brief 終了
 * 各コンテナに保持されている画像情報をクリア
*/
void TextureManager::Uninit(void)
{
	m_Textures.clear();
	m_SRVs.clear();
}
