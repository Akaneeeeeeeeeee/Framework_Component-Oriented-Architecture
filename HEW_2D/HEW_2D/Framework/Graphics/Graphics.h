#pragma once
#include "../Window/Window.h"
#include "../../Framework/Singleton_Template/Singleton_Template.h"

using namespace Microsoft::WRL;

//////////////////////////////////////////////////
//				DirectXフレームワーク				//
//////////////////////////////////////////////////
// TODO:ゲームクラスはD3D11クラスを継承するべき？メンバ変数にとどめておくべき？
// TODO:2024/10/4 D3D11のInit関数内をさらに関数分けする、エラー吐いてる部分が重要なのでそこの流れを理解する


class Graphics :public Singleton<Graphics>
{
public:

	Graphics();	//! コンストラクタ
	~Graphics();

	ID3D11Device* GetDevice(void);                 //!m_Deviceのゲッター
	ID3D11DeviceContext* GetDeviceContext(void);   //!m_DeviceContextのゲッター
	IDXGISwapChain* GetSwapChain(void);            //! スワップチェイン＝ダブルバッファ機能
	ID3D11Buffer* GetConstantBuffer(void);         //! 定数バッファ用変数
	HRESULT Init(HWND hwnd);		// 初期化（ゲームクラスではこの初期化が成功した場合→ゲームの初期化処理実行にする）
	void StartRender(void);			// 描画処理
	void FinishRender(void);		// 描画終了処理
	void Release(void);				// 終了処理

	//// シェーダー系生成
	//// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	//HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	//	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout);
	//// ピクセルシェーダーオブジェクトを生成
	//HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader);

	//// シェーダーコンパイル
	//HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

private:

	//--------------------------------------------------------------------------------------
	// メンバ変数（宣言したcpp内でのみ有効→どこでも使いたい場合はextern（外部参照）を使う）
	//--------------------------------------------------------------------------------------
	// ※ID3D11で始まるポインタ型の変数は、解放する必要がある
	// デバイス＝DirectXの各種機能を作る(これ一番重要。これがないと↓のGPUリソース(テクスチャ、バッファ、シェーダーなど)が作れない！)
	ComPtr<ID3D11Device> m_pDevice;
	// コンテキスト＝描画関連を司る機能(描画を実行するための機能、っていう感じ)
	ComPtr<ID3D11DeviceContext> m_pDeviceContext;
	// スワップチェイン＝ダブルバッファ機能(これはそのまま。現在描画中の画面の後ろで新しい画面を作っておいて、それを切り替える。)
	ComPtr<IDXGISwapChain> m_pSwapChain;
	// レンダーターゲット＝描画先を表す機能(GPUが描画する「最終的な出力先」を決める。例えば「画面全体に描画する」のか、「一部のテクスチャに描画する」のかを決める。)
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	// デプスバッファ＝Z値（奥行き情報）を管理する。近いオブジェクトを手前に、遠いオブジェクトを奥に描画。
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	// 最終的にGPUに送る定数バッファ用変数
	ComPtr<ID3D11Buffer> m_pConstantBuffer;

	// ＜ブレンドステート用変数（アルファブレンディング）＞
	// アルファ値をどの具合にブレンド(混ぜる)するかの「ブレンド方法」 を決める必要がある。
	// 単純に「このオブジェクトは半透明だよ！」と設定しても、どうやって透明度を計算するかが決まっていなければ、正しく描画できない。
	ComPtr<ID3D11BlendState> m_pBlendState;

	// ＜サンプラー用変数＞
	// 「テクスチャの拡大・縮小・フィルタリング方法」を指定する
	// テクスチャを正しく表示するために、どんな補間方法を使うか を指定する必要がある。
	// 設定しないと、意図しない表示になったり、ガタガタの見た目になる可能性がある。
	ComPtr<ID3D11SamplerState> m_pSampler;
};



// 構造体の定義
// 頂点データを表す構造体
struct Vertex
{
	// 頂点の位置座標
	float x, y, z;

	//色
	float r, g, b, a;

	// テクスチャ座標（UV座標）
	float u, v;
};

// 定数バッファ用構造体
struct ConstBuffer
{
	// 頂点カラー行列
	DirectX::XMFLOAT4 color;
	// UV座標移動行列
	DirectX::XMMATRIX matrixTex;
	// プロジェクション変換行列
	DirectX::XMMATRIX matrixProj;
	// ワールド変換行列
	DirectX::XMMATRIX matrixWorld;
};

// Direct3D解放の簡略化マクロ
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }
