#pragma once

#pragma warning(push)
#pragma warning(disable:4005)

#pragma warning(pop)

#pragma comment (lib,"winmm.lib")

#define _CRT_SECURE_NO_WARNINGS

// プリコンパイルヘッダー一覧
// 頻繁に使用するヘッダファイル一覧
#include <windows.h>
#include <assert.h>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <string>
#include <DirectXMath.h>	// DirextXの数学関連のヘッダーファイル
#include <SimpleMath.h>
#include <stdlib.h>
#include <algorithm>
#include <d3d11.h>			// DirectX11を使うためのヘッダーファイル

// DirectX::を省略したい
using namespace DirectX;

//! constexpr：コンパイル時に値が決まる定数
//! 変数と同じでスコープがあること、型を指定できること、コンパイル時（プログラム実行前）に値が決まる
//! →コンパイルどうのこうのはまだわからないので一旦放置、後から勉強
constexpr uint32_t SCREEN_WIDTH = 1920;
constexpr uint32_t SCREEN_HEIGHT = 1080;

// 定数定義
const auto ClassName = TEXT("HEW2D");			//!< ウィンドウクラス名.
const auto WindowName = TEXT("おとマトペ");		//!< ウィンドウ名.

