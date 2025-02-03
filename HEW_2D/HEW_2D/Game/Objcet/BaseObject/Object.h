#pragma once
#include "../../../Framework/ComponentManager/ComponentManager.h"
#include "../../ObjectManager/ObjectManager.h"


/**
 * @brief ベースとなるオブジェクトクラス
*/
class Object
{
public:
	Object();
	~Object();

private:
	std::string m_Name;
	Tag m_Tag;
	ComponentManager m_Componentmanager;
};

//Object::Object()
//{
//}
//
//Object::~Object()
//{
//}