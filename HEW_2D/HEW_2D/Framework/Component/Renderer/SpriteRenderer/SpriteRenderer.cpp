#include "SpriteRenderer.h"
#include "../../../ResourceManager/ResourceManager.h"


void SpriteRenderer::Init(void)
{
	// ���_��񏉊���
	m_Vertices = {
		//   x     y    z       r    g    b    a     u    v
		{ -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },	// 0�Ԗڂ̒��_���W
		{ 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },	// 1�Ԗڂ̒��_���W
		{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f },	// 2�Ԗڂ̒��_���W
		{ 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },	// 3�Ԗڂ̒��_���W
	};


	// ���_�o�b�t�@���쐬����
	// �����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;
	//bufferDesc.ByteWidth = sizeof(vertices);	// �m�ۂ���o�b�t�@�T�C�Y���w��ivector�Ȃ̂Œ��Ӂj
	bufferDesc.ByteWidth = static_cast<UINT>(m_Vertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = m_Vertices.data();	// VRAM�ɑ���f�[�^���w��ivector�Ȃ̂Œ��Ӂj
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = D3D11::GetInstance().GetDevice()->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
}


void SpriteRenderer::Update(void)
{
	
}


void SpriteRenderer::Uninit(void)
{
	m_pShader.reset();
}


/**
 * @brief �e�N�X�`���ݒ�
 * @param _ID �o�^����Ă���ID
 * @param _split �摜������
*/
void SpriteRenderer::SetTexture(TextureID _ID, XMINT2 _split)
{
	// ���\�[�X�}�l�[�W���ɓo�^����Ă���ID����SRV���擾���ēo�^
	this->m_pTextureView = ResourceManager::GetInstance().GetSRV(_ID);
	// �������ݒ�
	this->m_Split = _split;
	m_Vertices[1].u = 1.0f / m_Split.x;
	m_Vertices[2].v = 1.0f / m_Split.y;
	m_Vertices[3].u = 1.0f / m_Split.x;
	m_Vertices[3].v = 1.0f / m_Split.y;
}

/**
 * @brief �V�F�[�_�[�ݒ�
 * @param _shader ���\�[�X�}�l�[�W�����玝���Ă����V�F�[�_�[��shared_ptr
*/
void SpriteRenderer::SetShader(std::shared_ptr<Shader> _shader)
{
	this->m_pShader = _shader;
}
