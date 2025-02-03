#pragma once
#include "../../../Framework/ComponentManager/ComponentManager.h"
#include "../../ObjectManager/ObjectManager.h"


/**
 * @brief �x�[�X�ƂȂ�I�u�W�F�N�g�N���X
 * 
 * ��{��2D�I�u�W�F�N�g��`�悷�邽�߂ɕK�v�ȃR���|�[�l���g
 * �ESpriteRenderer
 * �ERigidBody2D
 * �EBoxCollider
 * �E
*/
class Object :public std::enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();



	//-----------------------
	//-----�e���v���[�g�֐�-----
	//-----------------------

	/**
	 * @brief �R���|�[�l���g�ǉ��֐�
	 * @tparam T �R���|�[�l���g
	 * @return �R���|�[�l���g��weak_ptr���Ԃ�������lock()�֐����g��Ȃ��ƃ|�C���^���g���Ȃ�
	*/
	template <class T>
	std::weak_ptr<T> AddComponent(void)
	{
		//! �R���|�[�l���g�̃|�C���^�𐶐�
		auto component = std::make_shared<T>();
		//! ���������R���|�[�l���g�����ɑ��݂��Ă����
		if (m_Components.find(std::type_index(typeid(T))) != m_Components.end())
		{
			throw std::runtime_error("����R���|�[�l���g�����ɑ��݂��Ă��܂�");
		}
		//! �Ȃ���΃R���|�[�l���g�ɒǉ�
		component->Init();
		m_Components.emplace(std::type_index(typeid(T)), component);
		//! �R���|�[�l���g�̃|�C���^��Ԃ�
		return std::weak_ptr<T>(component);
	}


	/**
	 * @brief �R���|�[�l���g�擾�֐�
	 * @tparam T �R���|�[�l���g�̌^
	 * @return �R���|�[�l���g�̃|�C���^
	*/
	template <class T>
	std::shared_ptr<T> GetComponent(void)
	{
		//! ���̃R���|�[�l���g�����݂��Ă��邩��T��
		for (auto& component : m_Components)
		{
			// ���̃R���|�[�l���g�̌^�ɃL���X�g�ł����
			if (T* comp = dynamic_cast<T*>(component.second.get()))
			{
				//! �R���|�[�l���g�̃|�C���^��Ԃ�
				return std::shared_ptr<T>(component.second, comp);
			}
		}
		//! �Ȃ���΃G���[�o��
		std::cerr << typeid(T).name() << "��ێ����Ă��܂���" << std::endl;
	}

private:
	std::string m_Name;
	Tag m_Tag;
	
	// ���ꂢ��Ȃ��ˁH�Q�[���I�u�W�F�N�g�̒��̃R���|�[�l���g�}�l�[�W�����炶��Ȃ���addcomponent�ł��Ȃ����I�u�W�F�N�g��map�ŊǗ����Ƃ��ق�������
	//ComponentManager m_ComponentManager;

	// �R���|�[�l���g��map
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> m_Components;

};

//Object::Object()
//{
//}
//
//Object::~Object()
//{
//}