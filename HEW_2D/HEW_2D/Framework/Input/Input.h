#pragma once

#include <Xinput.h> //XInputを使うためのヘッダーファイル
#pragma comment (lib, "xinput.lib") //XInputを使うために必要


#define XINPUT_A              0x1000
#define XINPUT_B              0x2000
#define XINPUT_X              0x4000
#define XINPUT_Y              0x8000
#define XINPUT_UP             0x0001
#define XINPUT_DOWN           0x0002
#define XINPUT_LEFT           0x0004
#define XINPUT_RIGHT          0x0008
#define XINPUT_START          0x0010
#define XINPUT_BACK           0x0020
#define XINPUT_LEFT_THUMB     0x0040 //左スティック押し込み
#define XINPUT_RIGHT_THUMB    0x0080 //右スティック押し込み
#define XINPUT_LEFT_SHOULDER  0x0100 //L
#define XINPUT_RIGHT_SHOULDER 0x0200 //R
#define TRIGGER_THRESHOLD 30		 //ZRとZLの押し込み感度の高さ

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x45
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


/**
 * @brief 入力管理クラス
 * 
 * 静的クラスでもいいのかなと思ったけど、どうやらシングルトンのほうがいいらしい
 * →静的クラスだと状態の管理が難しいみたい（あまりよくわかってない）
*/
class Input {
private:
	//キー入力情報を保存する変数
	BYTE keyState[256] = {};
	BYTE keyState_old[256] = {};

	//コントローラー入力情報を保存する変数
	XINPUT_STATE controllerState = {};
	XINPUT_STATE controllerState_old = {};

	int VibrationTime;	//振動継続時間をカウントする変数


	//! コンストラクタとデストラクタをprivateに配置することで、インスタンスを生成できなくする
	//! コンストラクタとデストラクタは変数が作られたときと消えるときに動作する関数
	//! つまり、インスタンスを作ろうとする→コンストラクタが動こうとするけどprivateだから動かない→インスタンスが作れない
	//! となる
	Input();			//コンストラクタ
	~Input();			//デストラクタ


public:

	static Input& GetInstance(void);	// インスタンス取得関数

	void Update(); //更新

	//キー入力
	bool GetKeyPress(int key);   //プレス(押している間ずっと)
	bool GetKeyTrigger(int key); //トリガー(押し始めた時)
	bool GetKeyRelease(int key); //リリース(押し終わった時)

	//ZRとZLの入力判定
	bool IzZRPressed();
	bool IzZLPressed();

	//アナログスティック(コントローラー)
	DirectX::XMFLOAT2 GetLeftAnalogStick(void);
	DirectX::XMFLOAT2 GetRightAnalogStick(void);

	//トリガー(コントローラー)
	float GetLeftTrigger(void);
	float GetRightTrigger(void);

	//ボタン入力(コントローラー)
	bool GetButtonPress(WORD btn);   //プレス(押している間ずっと)
	bool GetButtonTrigger(WORD btn); //トリガー(押し始めた時)
	bool GetButtonRelease(WORD btn); //リリース(押し終わった時)

	//振動(コントローラー)
	//flame：振動を継続する時間(単位：フレーム)
	//power：振動の強さ(0〜1)
	void SetVibration(int frame = 1, float powor = 1);
};

#pragma once
