#pragma once
#include "../Onomatopeia/IOnomatopoeia/IOnomatopoeia.h"

/**
 * @brief 擬音銃に使うマガジンクラス
 * →これをコンテナの配列にしてプレイヤーのメンバとして保持する
 * 
 * 〇メンバ変数
 * 　・銃に装填されているか？
 * 　・マガジン内部が空かどうか？
 * 
 * ・マガジン画像以外に擬音の画像が必要
 * ・当たり判定は不要
 * 
 * 
 * マガジン(一個目)
 * →初期化時にプレイヤーの
 * 
 * マガジンのUI(二個目以降)
 * →まずマガジンをオブジェクトして配置
 * 　→プレイヤーとだけ当たり判定を取る
 * 　　→プレイヤーが取得したらタグをUIに変更
 * 　　　→座標、スケールを変更して画面上の任意の場所に表示させる
 * 
*/
class Magazine : public Object
{
public:
	Magazine(const UINT& _ID, const Tag& _tag, const std::string& _name);
	
	~Magazine();

	void Update(void);		// 擬音の状態などをこっちで管理するためにオーバーライド
	void Draw(void);		// 擬音装填したときにそれも描画するのでオーバーライド
	// マガジンに入った場合、その擬音の所有権はマガジンに移るはずなのでunique_ptr
	//void SetOnomatopoeia(Tag, std::string, std::shared_ptr<GameObject>&& _onomatopoeia);

	// 擬音の情報を取得
	IOnomatopoeia* GetBulletPointer(void);

	// 擬音をマガジンに装填する関数
	void SetOnomatopoeia(std::shared_ptr<IOnomatopoeia> _onomat);

	// 発射時に擬音の所有権を擬音銃に渡してマガジン内を空にする関数
	std::shared_ptr<IOnomatopoeia> ReleaseBullet(void);

private:
	bool IsFlying;		// 飛んでいるか？
	std::shared_ptr<IOnomatopoeia> m_Onomatopoeia;
};

