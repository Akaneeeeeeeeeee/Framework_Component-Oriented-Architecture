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
	SpriteRenderer(GameObject* _Owner) :IComponent(_Owner) {};
	~SpriteRenderer() {};

private:
	//! ���_�f�[�^
	//! ���̃Q�[���ł͋[�����z�����ނ��Ƃ����邽�ߒ��_���ςɂ��Ă���
	std::vector<Vertex> m_Vertices;

	// �F
	Color m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// ���_�o�b�t�@
	ComPtr<ID3D11Buffer> m_pVertexBuffer;

	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	// �e�N�X�`���p�ϐ�
	ComPtr<ID3D11ShaderResourceView> m_pTextureView;

	//�e�N�X�`�����c���ɉ���������Ă��邩
	XMINT2 m_Split = { 1,1 };

	//���ォ�牽�i�ڂ�؂蔲���ĕ\�����邩
	XMINT2 m_Number = { 0,0 };
};

