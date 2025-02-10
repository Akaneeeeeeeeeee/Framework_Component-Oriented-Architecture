#include "Singleton_Template.h"

template <class T>
T& Singleton<T>::GetInstance(void)
{
	// 静的ポインタ変数としてシングルトンのインスタンスを保持する
	static T Instance;

	// インスタンスを返す
	return Instance;
}

