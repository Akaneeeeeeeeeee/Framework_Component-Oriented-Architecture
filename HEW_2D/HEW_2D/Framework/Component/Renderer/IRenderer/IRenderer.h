#pragma once
#include "../../IComponent/IComponent.h"


/**
 * @brief �����_���[�n�R���|�[�l���g�����ʂ��邽�߂̃C���^�[�t�F�[�X�N���X
*/
class IRenderer:public IComponent
{
public:
	IRenderer();
	IRenderer(Object* _Owner) :IComponent(_Owner) {};

	~IRenderer() {};

	virtual void Render(void) = 0;

private:

};

