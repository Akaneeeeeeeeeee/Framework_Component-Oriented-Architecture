#pragma once
#include "../../IComponent/IComponent.h"
#include "../../../D3D11/D3D11.h"

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

/**
 * @brief �摜�`��R���|�[�l���g
 * 
 * ���_���W
 * ���_���
 * �C���f�b�N�X�o�b�t�@
 * �摜���
*/
class SpriteRenderer :public IComponent
{
public:
	SpriteRenderer() = delete;
	SpriteRenderer(GameObject* _Owner) :IComponent(_Owner) 
	{

	}
	
	/**
	 * @brief �f�X�g���N�^
	*/
	~SpriteRenderer() {
		// ComPtr(�X�}�[�g�|�C���^)�Ȃ̂ŉ������K�v�͂Ȃ����A�ꉞ�����I�ɉ�����Ă���
		m_pVertexBuffer.Reset();
		m_pIndexBuffer.Reset();
		m_pTextureView.Reset();
	};

	void Init(void) override;
	void Update(void) override;
	void Uninit(void) override;

	// �摜�ƕ��������Z�b�g����
	void SetTexture(const wchar_t* imgname, XMINT2 _Num = { 1,1 });

private:
	//! ���_�f�[�^
	std::vector<Vertex> m_Vertices;

	// �F
	Color m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// �����_�o�b�t�@��
	// ���_�f�[�^�i���W�A�F�AUV���W�A�@���Ȃǁj��GPU�ɑ��邽�߂̃o�b�t�@
	// ���_���Ƃ̏����i�[���AGPU�ɓn���BGPU�͂��̃f�[�^�� ���_�V�F�[�_�[�iVertex Shader�j �ɓn���ď�������B
	ComPtr<ID3D11Buffer> m_pVertexBuffer;

	// ���C���f�b�N�X�o�b�t�@��
	// ���_�̌��ԏ��ԁi�`�悷�鏇���j��GPU�ɑ��邽�߂̃o�b�t�@
	// ���_�o�b�t�@�Ɋi�[���ꂽ ���_�̏��� ���w�肷��BGPU�� �C���f�b�N�X�o�b�t�@ ���g���A���_�� �K�؂ȏ��ԂŃV�F�[�_�[�ɓn���ĕ`�悷��B
	ComPtr<ID3D11Buffer> m_pIndexBuffer;

	// ���e�N�X�`���p�ϐ�(�摜���)��
	/*
	�EGPU���e�N�X�`���i�摜�j�� �s�N�Z���V�F�[�_�[�iPixel Shader�j �Ŏg���Ƃ��ɎQ�Ƃ�����́B
	�E�����̉摜�f�[�^�ł͂Ȃ��A�u�V�F�[�_�[���ǂ̂悤�ɎQ�Ƃ��邩�v���`�������������
	�E�摜�f�[�^���V�F�[�_�[��������悤�ɂ���r���[
	�E�e�N�X�`���i�摜�f�[�^�j���̂��̂ł͂Ȃ��A����ɃA�N�Z�X���邽�߂̃C���^�[�t�F�[�X �Ƃ����C���[�W
	�E�摜�f�[�^�iID3D11Texture2D�j�͂����̃s�N�Z���̏W�܂� �� GPU�����̂܂܎g���ɂ͏�񂪑���Ȃ�
	�E�X�v���C�g�摜�ꖇ�Ȃ�texture2D�g��Ȃ��Ă��������ǁA�ʂ̉摜��ێ������Ă��������ꍇ�Atexture2d���������Ă����ׂ����Ă��ƁH�i����͔z�񂩂ȁH�킩��Ȃ����ǁB�j
	�@�ŁA��{�I�ɂ�texture2d��srv�̓Z�b�g�Ŏ������Ă������Ă����F����OK�H
	*/
	// �����摜���g�������ꍇ(�~�b�v�}�b�v(�𑜓x���Ƃɉ摜�𕪂��ĊǗ�)�Ƃ�)�Atexture2d���Ή��t���Ď������Ȃ��ƃ_��
	// ������͉摜�t�@�C�����璼��SRV�����̂�Texture2D�͎g��Ȃ�
	ComPtr<ID3D11ShaderResourceView> m_pTextureView;


	// ���u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�j��
	// �A���t�@�l���ǂ̋�Ƀu�����h(������)���邩�́u�u�����h���@�v �����߂�K�v������B
	// �P���Ɂu���̃I�u�W�F�N�g�͔���������I�v�Ɛݒ肵�Ă��A�ǂ�����ē����x���v�Z���邩�����܂��Ă��Ȃ���΁A�������`��ł��Ȃ��B
	ComPtr<ID3D11BlendState> m_pBlendState;

	// ���T���v���[�p�ϐ���
	// �u�e�N�X�`���̊g��E�k���E�t�B���^�����O���@�v���w�肷��
	// �e�N�X�`���𐳂����\�����邽�߂ɁA�ǂ�ȕ�ԕ��@���g���� ���w�肷��K�v������B
	// �ݒ肵�Ȃ��ƁA�Ӑ}���Ȃ��\���ɂȂ�����A�K�^�K�^�̌����ڂɂȂ�\��������B
	ComPtr<ID3D11SamplerState> m_pSampler;

	// �e�N�X�`�����c���ɉ���������Ă��邩
	XMINT2 m_Split = { 1,1 };

	// ���ォ�牽�i�ڂ�؂蔲���ĕ\�����邩
	XMINT2 m_Number = { 0,0 };
};

