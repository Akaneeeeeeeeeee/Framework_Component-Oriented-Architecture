#include "DebugFunction.h"
#include "../DebugUI.h"
#include "../../../GolfBall.h"


namespace DebugFunction {
	//! �v���C���[���\��
	void DebugPlayer(void) {
		ImGui::Begin("Debug Player");
		ImGui::Text("Position: %f %f %f",GolfBall::Object::GetPosition().x)
	}

	//! �v���C���[����p�X���C�_�[
	void DebugPlayerSlider(void);
}
