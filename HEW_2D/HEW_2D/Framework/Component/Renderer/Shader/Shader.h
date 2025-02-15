#pragma once
#include "../../../D3D11/D3D11.h"

using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

/**
 * @brief �V�F�[�_�[�ɕK�v�ȏ����܂Ƃ߂��N���X(�����Renderer�Ƃ����Ǘ�����)
*/
class Shader
{
public:
	Shader();
	~Shader();

	void Init(void);

private:
	//-----�V�F�[�_�[�n-----//
	// ���̓��GPU�ɓo�^���ꂽ�V�F�[�_�[�v���O�����ւ̎Q�Ɓ�GPU��̃V�F�[�_�[�̃n���h���v���Ǝv����OK�I
	// �����_�V�F�[�_�[�I�u�W�F�N�g��
	// ���_�f�[�^�����H���ĉ�ʏ�̐������ʒu�ɕϊ��B
	// �X�v���C�g��I�u�W�F�N�g�̈ʒu�A�X�P�[���A��]�A�ό`���s���B����ɂ��A�`��Ώۂ���ʏ�̓K�؂Ȉʒu�ɕϊ�������A�A�j���[�V������������ł���
	ComPtr<ID3D11VertexShader> m_pVertexShader;

	// ���s�N�Z���V�F�[�_�[�I�u�W�F�N�g��
	// �e�N�X�`�����T���v�����O���čŏI�I�ȐF������B
	// �e�N�X�`���̐F��A���t�@�l�i�����x�j���v�Z����B���Ƃ��΁A�X�v���C�g�̐F��ύX������A�e�N�X�`���̈ꕔ����荞��ŕ\�����邱�Ƃ��ł���B
	ComPtr<ID3D11PixelShader> m_pPixelShader;

	// ���C���v�b�g���C�A�E�g��
	// �X�v���C�g�̒��_�f�[�^�� (���W + UV���W) �������Ă邯�ǁA3D���f���̒��_�f�[�^�� (���W + �@�� + UV���W) �݂����ɍ\�����Ⴄ�B
	// DirectX�́A�u���̒��_�f�[�^�̂��̕��������W�ŁA���̕�����UV���W�ł���I�v���Ă�������m��Ȃ��ƁA�������`��ł��Ȃ��B
	// �̂ŁAID3D11InputLayout �Łu���̒��_�f�[�^�͂��������\���ɂȂ��Ă��v�Ƌ����Ă�����K�v������I
	// �X�v���C�g�̒��_�f�[�^��n�����߂ɕێ����Ă���(����͊�{���_�V�F�[�_�[�ƃZ�b�g�Ŏg��)
	ComPtr<ID3D11InputLayout> m_pVertexLayout;
};

Shader::Shader()
{
}

Shader::~Shader()
{
}
