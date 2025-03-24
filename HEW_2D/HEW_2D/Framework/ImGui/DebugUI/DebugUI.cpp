#include "DebugUI.h"

// �f�o�b�O�֐����i�[����ÓI�����o�ϐ�
std::vector<std::function<void(void)>> DebugUI::m_DebugFunction;

// ImGui�̏��������s���֐�
void DebugUI::Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    //! ImGui�̏�����
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // �L�[�{�[�h�����L���ɂ���
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // �Q�[���p�b�h�����L���ɂ���

    // Dear ImGui�̃X�^�C����ݒ�
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // �v���b�g�t�H�[��/�����_���[�̃o�C���f�B���O��ݒ�
    ImGui_ImplWin32_Init(Application::GetWindow());
    ImGui_ImplDX11_Init(_device, _deviceContext);
}

// �f�X�g���N�^�FImGui�̏I���������s��
DebugUI::~DebugUI() {
    //! �I��
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

// �f�o�b�O�֐���o�^����֐�
void DebugUI::RegisterDebugFunction(std::function<void(void)> _func)
{
    m_DebugFunction.push_back(std::move(_func));
}

// ImGui�̃����_�����O���s���֐�
void DebugUI::Render(void) {
    //! ImGui�̐V�����t���[�����J�n
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    //! �E�B���h�E�ƃf�o�b�O���̕`��
    ImGui::Begin("Debug Information");
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average % 3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    //! �f�o�b�O�֐��̎��s
    for (auto& func : m_DebugFunction)
    {
        func();
    }

    //! �t���[���̃����_�����O������
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
