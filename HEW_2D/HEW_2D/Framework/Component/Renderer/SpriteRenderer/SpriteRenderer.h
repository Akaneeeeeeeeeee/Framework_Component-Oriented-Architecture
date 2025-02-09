#pragma once
#include "../../IComponent/IComponent.h"


/**
 * @brief 画像描画コンポーネント
 * 
 * 頂点座標
 * 頂点情報
*/
class SpriteRenderer :public IComponent
{
public:
	SpriteRenderer() = delete;
	SpriteRenderer(GameObject* _Owner) :IComponent(_Owner) {};
	~SpriteRenderer() {};

private:

};

