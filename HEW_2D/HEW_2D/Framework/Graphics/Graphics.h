#pragma once
#include "../Window/Window.h"
#include "../../Framework/Singleton_Template/Singleton_Template.h"

using namespace Microsoft::WRL;

//////////////////////////////////////////////////
//				DirectX�t���[�����[�N				//
//////////////////////////////////////////////////
// TODO:�Q�[���N���X��D3D11�N���X���p������ׂ��H�����o�ϐ��ɂƂǂ߂Ă����ׂ��H
// TODO:2024/10/4 D3D11��Init�֐���������Ɋ֐���������A�G���[�f���Ă镔�����d�v�Ȃ̂ł����̗���𗝉�����


class Graphics :public Singleton<Graphics>
{
public:

	Graphics();	//! �R���X�g���N�^
	~Graphics();

	ID3D11Device* GetDevice(void);                 //!m_Device�̃Q�b�^�[
	ID3D11DeviceContext* GetDeviceContext(void);   //!m_DeviceContext�̃Q�b�^�[
	IDXGISwapChain* GetSwapChain(void);            //! �X���b�v�`�F�C�����_�u���o�b�t�@�@�\
	ID3D11Buffer* GetConstantBuffer(void);         //! �萔�o�b�t�@�p�ϐ�
	HRESULT Init(HWND hwnd);		// �������i�Q�[���N���X�ł͂��̏����������������ꍇ���Q�[���̏������������s�ɂ���j
	void StartRender(void);			// �`�揈��
	void FinishRender(void);		// �`��I������
	void Release(void);				// �I������

	//// �V�F�[�_�[�n����
	//// ���_�V�F�[�_�[�I�u�W�F�N�g�𐶐��A�����ɒ��_���C�A�E�g������
	//HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	//	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout);
	//// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g�𐶐�
	//HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader);

	//// �V�F�[�_�[�R���p�C��
	//HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut);

private:

	//--------------------------------------------------------------------------------------
	// �����o�ϐ��i�錾����cpp���ł̂ݗL�����ǂ��ł��g�������ꍇ��extern�i�O���Q�Ɓj���g���j
	//--------------------------------------------------------------------------------------
	// ��ID3D11�Ŏn�܂�|�C���^�^�̕ϐ��́A�������K�v������
	// �f�o�C�X��DirectX�̊e��@�\�����(�����ԏd�v�B���ꂪ�Ȃ��Ɓ���GPU���\�[�X(�e�N�X�`���A�o�b�t�@�A�V�F�[�_�[�Ȃ�)�����Ȃ��I)
	ComPtr<ID3D11Device> m_pDevice;
	// �R���e�L�X�g���`��֘A���i��@�\(�`������s���邽�߂̋@�\�A���Ă�������)
	ComPtr<ID3D11DeviceContext> m_pDeviceContext;
	// �X���b�v�`�F�C�����_�u���o�b�t�@�@�\(����͂��̂܂܁B���ݕ`�撆�̉�ʂ̌��ŐV������ʂ�����Ă����āA�����؂�ւ���B)
	ComPtr<IDXGISwapChain> m_pSwapChain;
	// �����_�[�^�[�Q�b�g���`����\���@�\(GPU���`�悷��u�ŏI�I�ȏo�͐�v�����߂�B�Ⴆ�΁u��ʑS�̂ɕ`�悷��v�̂��A�u�ꕔ�̃e�N�X�`���ɕ`�悷��v�̂������߂�B)
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	// �f�v�X�o�b�t�@��Z�l�i���s�����j���Ǘ�����B�߂��I�u�W�F�N�g����O�ɁA�����I�u�W�F�N�g�����ɕ`��B
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	// �ŏI�I��GPU�ɑ���萔�o�b�t�@�p�ϐ�
	ComPtr<ID3D11Buffer> m_pConstantBuffer;

	// ���u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j��
	// �A���t�@�l���ǂ̋�Ƀu�����h(������)���邩�́u�u�����h���@�v �����߂�K�v������B
	// �P���Ɂu���̃I�u�W�F�N�g�͔���������I�v�Ɛݒ肵�Ă��A�ǂ�����ē����x���v�Z���邩�����܂��Ă��Ȃ���΁A�������`��ł��Ȃ��B
	ComPtr<ID3D11BlendState> m_pBlendState;

	// ���T���v���[�p�ϐ���
	// �u�e�N�X�`���̊g��E�k���E�t�B���^�����O���@�v���w�肷��
	// �e�N�X�`���𐳂����\�����邽�߂ɁA�ǂ�ȕ�ԕ��@���g���� ���w�肷��K�v������B
	// �ݒ肵�Ȃ��ƁA�Ӑ}���Ȃ��\���ɂȂ�����A�K�^�K�^�̌����ڂɂȂ�\��������B
	ComPtr<ID3D11SamplerState> m_pSampler;
};



// �\���̂̒�`
// ���_�f�[�^��\���\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;

	//�F
	float r, g, b, a;

	// �e�N�X�`�����W�iUV���W�j
	float u, v;
};

// �萔�o�b�t�@�p�\����
struct ConstBuffer
{
	// ���_�J���[�s��
	DirectX::XMFLOAT4 color;
	// UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;
	// �v���W�F�N�V�����ϊ��s��
	DirectX::XMMATRIX matrixProj;
	// ���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;
};

// Direct3D����̊ȗ����}�N��
#define SAFE_RELEASE(p) { if( NULL != p ) { p->Release(); p = NULL; } }
