#include"TestScene.h"
#include "../../Game/Objcet/Player/Player.h"
#include "../../Game/Objcet/Enemy/Enemy.h"
#include "../../Framework/Input/Input.h"
#include "../../Game/Objcet/Onomatopeia/Poyon/Poyon.h"
#include "../../Game/Objcet/Onomatopeia/PataPata/PataPata.h"
#include "../../Game/Objcet/Onomatopeia/BiriBiri/BiriBiri.h"
#include "../../Framework/Component/Collider/2D/BoxCollider2D/BoxCollider2D.h"


/**
 * @brief �^�C�g���V�[���̏�����
 *
 * �V�[�����Ƃɏ������͍ŏ��̈�x�̂�
 * ��
 *
 * �X�e�[�W�́A�c�Q�O�}�X�����S�O�}�X
*/

void TestScene::Init(void) {
	//sound.Init();

	// �I�u�W�F�N�g�}�l�[�W��������
	objectmanager.Init();
	//sound.Init();


	//-----------------------
	//-----�I�u�W�F�N�g�ǉ�-----
	//-----------------------
	// TODO:1218�����܂� �I�u�W�F�N�g�̊Ǘ���enum����ύX��tag�Ɩ��O�ɂ�����
	
	
	std::cout << "TitleSceneInit" << std::endl;

	std::cout << "GameSceneInit" << std::endl;

}




void TestScene::Update(void)
{
	Input::GetInstance().Update();
	// �X�e�B�b�N���͒l���擾
	Vector2 RightStickInput = Input::GetInstance().GetRightAnalogStick();	// �E�X�e�B�b�N����
	Vector2 LeftStickInput = Input::GetInstance().GetLeftAnalogStick();		// ���X�e�B�b�N����

	//sound.Play(SOUND_LABEL_BGM000);


	// ���͏��̍X�V
	// �V�[���X�V�ɕK�v�ȏ����擾
	
	//objectmanager.Collider_Player_to_Object();		// �����œ���������}�K�W�������P���炷

	objectmanager.Update();

}

void TestScene::Draw(void) {
	objectmanager.Draw();
}

void TestScene::Uninit(void) {
	objectmanager.Uninit();
	//sound.Uninit();

}
