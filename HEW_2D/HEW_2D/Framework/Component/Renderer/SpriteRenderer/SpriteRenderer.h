#pragma once
#include "../../IComponent/IComponent.h"


/**
 * @brief �摜�`��R���|�[�l���g
 * 
 * ���_���W
 * ���_���
*/
class SpriteRenderer :public IComponent
{
public:
	SpriteRenderer() = delete;
	SpriteRenderer(GameObject* _Owner) :IComponent(_Owner) {};
	~SpriteRenderer() {};

private:

};

