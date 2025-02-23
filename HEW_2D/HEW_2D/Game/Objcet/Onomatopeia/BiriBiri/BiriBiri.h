#pragma once
#include "../IOnomatopoeia/IOnomatopoeia.h"

class BiriBiri :public IOnomatopoeia
{
public:
	BiriBiri(const UINT& _ID, const Tag& _tag, const std::string& _name) :IOnomatopoeia(_ID, _tag, _name) {
		knockback_power = 10;
		BiriBiri_check = false;
	}
	~BiriBiri();	//�f�X�g���N�^
	void Action(void) {};
	void Action(std::weak_ptr<Object>);		//�r���r�������̊֐�

	bool BiriBiri_check;
	void Set_Onomatope(bool)override;//�[����Action�֐��𓮂������߂̃Q�b�^�[�A�Z�b�^�[
	bool Get_Onomatope(void)override;
	void Set_gion(bool)override;
	bool Get_gion(void)override;
private:
	float knockback_power;//�m�b�N�o�b�N�p���[
};
