#pragma once
#include "../../Framework/Scene/IScene.h"
#include "../ObjectManager/ObjectManager.h"


/**
 * @brief �Q�[���V�[��
 * 
 * �V�[���̔h���S���e���v���[�g�ł悭�Ȃ����H�B�B�B���|�����[�t�B�Y���ŊǗ��ł��Ȃ�����NG!
*/
class GameScene :public IScene
{
public:
	GameScene() :IScene() {};
	~GameScene() {};
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Uninit(void)override;

private:

};

