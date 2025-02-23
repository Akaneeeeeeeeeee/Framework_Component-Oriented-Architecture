#pragma once
#include "../../../Framework/ComponentManager/ComponentManager.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../../Framework/Component/Transform/TransformComponent.h"
#include "../../../Framework/Component/RigitBody/RigitBody2D.h"

/**
 * @brief �I�u�W�F�N�g�Ǘ��^�O
*/
enum Tag {
	NONE = -1,		// �f�t�H���g�l
	BACKGROUND,
	IMAGE,
	UI,
	OBJECT,
	GROUND,
	ONOMATOPOEIA,
	PLAYER,
	ENEMY,
	CAMERA,


	TAG_MAX
};

// �I�u�W�F�N�g�̏�ԁi�����ɑS�������o���Ă����j
enum STATE
{
	NORMAL,		// �ʏ펞
	RUN,		// �ړ���
	JUMP,		// �W�����v��
	DAMAGED,	// ��_����
	ATTACKED,	// �U����
	EFECT,      //�G�t�F�N�g
};

/**
 * @brief �x�[�X�ƂȂ�I�u�W�F�N�g�N���X
 * 
 * ��{��2D�I�u�W�F�N�g��`�悷�邽�߂ɕK�v�ȃR���|�[�l���g
 * �ESpriteRenderer
 * �ERigidBody2D
 * �EBoxCollider
 * �E
 * 
 * �R���|�[�l���g�}�l�[�W������邱�Ƃ��l�������A�����ւ̃A�N�Z�X���镪���Ԃ��������Ȃ��̂ł́��I�u�W�F�N�g�����Ŏ��悤�ɂ���(�K�v������Όォ��ύX)
*/
class Object :public std::enable_shared_from_this<Object>
{
public:
	Object() {
		// �R���X�g���N�^��Transform�R���|�[�l���g���������Œǉ����Ă���
		AddComponent<TransformComponent>(this);
	};

	Object(const UINT& _ID, const Tag& _tag, const std::string& _name) :m_ID(_ID), m_Tag(_tag), m_Name(_name) {
		// �R���X�g���N�^��Transform�R���|�[�l���g���������Œǉ����Ă���
		AddComponent<TransformComponent>(this);
	};


	virtual ~Object() {};

	//-----------------------
	//-----�e���v���[�g�֐�-----
	//-----------------------

	/**
	 * @brief �R���|�[�l���g�ǉ��֐�
	 * @tparam T �R���|�[�l���g
	 * @return �R���|�[�l���g�̐��|�C���^
	*/
	template <class T>
	T* AddComponent(Object* _Owner)
	{
		////! �R���|�[�l���g�̃|�C���^�𐶐�
		//auto component = std::make_shared<T>();
		////! ���������R���|�[�l���g�����ɑ��݂��Ă����
		//if (m_Components.find(std::type_index(typeid(T))) != m_Components.end())
		//{
		//	throw std::runtime_error("����R���|�[�l���g�����ɑ��݂��Ă��܂�");
		//}
		////! �Ȃ���΃R���|�[�l���g�ɒǉ�
		//component->Init();
		//m_Components.emplace(std::type_index(typeid(T)), component);
		////! �R���|�[�l���g�̃|�C���^��Ԃ�
		//return std::weak_ptr<T>(component);

		// �R���p�C�����`�F�b�N
		static_assert(std::is_base_of<IComponent, T>::value, "T �� Component ���p�����Ă���K�v������܂�");
		static_assert(std::is_constructible<T, Object*>::value, "T �� Object* ���󂯎��R���X�g���N�^�����K�v������܂�");

		// �R���|�[�l���g�̌^���擾
		std::type_index type = typeid(T);

		// ���ɓ����^�̃R���|�[�l���g�����݂���ꍇ�A�G���[�𓊂���
		if (m_Components.find(type) != m_Components.end()) {
			throw std::runtime_error("����R���|�[�l���g�����ɑ��݂��Ă��܂�");
		}

		// �R���|�[�l���g�𐶐����A���L����
		auto component = std::make_unique<T>(_Owner);
		component->Init();

		// �R���|�[�l���g��o�^
		m_Components.emplace(type, std::move(component));

		return component.get();
	}


	/**
	 * @brief �R���|�[�l���g�擾�֐�
	 * @tparam T �R���|�[�l���g�̌^
	 * @return �R���|�[�l���g�̐��|�C���^
	*/
	template <class T>
	T* GetComponent(void)
	{
		// �R���|�[�l���g�̌^���擾
		std::type_index type = typeid(T);

		//! ���̃R���|�[�l���g�����݂��Ă��邩��T��
		auto it = m_Components.find(type);
		if (it != m_Components.end())
		{
			// �ړI�̌^�ɃL���X�g���ĕԂ�
			return dynamic_cast<T>(it->second.get());
		}

		// �Ȃ���΃G���[�o��
		std::cerr << typeid(T).name() << " ��ێ����Ă��܂���" << std::endl;
		return nullptr;  // �R���|�[�l���g��������Ȃ���� nullptr ��Ԃ�
	}

	/**
	 * @brief "�S"�R���|�[�l���g���擾����֐�
	 * @tparam T 
	 * @param  
	 * @return 
	 * 
	 * �����̋@�\�g����ʂ��z���ł��Ȃ��̂ō��̈�U�~�߂Ƃ��B�K�v�ɂȂ�������I
	*/
	/*template <class T>
	std::vector<IComponent> GetComponents(void)
	{

	}*/


	//----------------------------
	//			��{�֐�
	//----------------------------
	virtual void Init(void);
	virtual void Update(void);
	// �`��͍X�V�������ōs���H�֐���������Ă����āA�`��R���|�[�l���g������ꍇ�ɏ������s���H
	virtual void Draw(void);
	virtual void Uninit(void);

	const virtual Tag& GetTag(void) { return m_Tag; }
	const virtual std::string& GetName(void) { return m_Name; }


protected:
	// �e�I�u�W�F�N�g�̃|�C���^
	Object* m_pParent;
	// �q�I�u�W�F�N�g�̃|�C���^


	UINT m_ID;
	std::string m_Name = "GameObject";
	Tag m_Tag = NONE;
	
	// ���ꂢ��Ȃ��ˁH�Q�[���I�u�W�F�N�g�̒��̃R���|�[�l���g�}�l�[�W�����炶��Ȃ���addcomponent�ł��Ȃ����I�u�W�F�N�g��map�ŊǗ����Ƃ��ق�������
	//ComponentManager m_ComponentManager;

	// �R���|�[�l���g��map(���L�����|���̂�unique�ŊǗ�)
	std::unordered_map<std::type_index, std::unique_ptr<IComponent>> m_Components;

};
