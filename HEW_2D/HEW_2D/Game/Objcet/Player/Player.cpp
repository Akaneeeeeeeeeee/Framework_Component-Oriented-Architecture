#include "Player.h"
#include "../../../Framework/Input/Input.h"


/**
 * @brief 更新
*/
void Player::Update(void)
{
	// 方向ベクトル初期化
	m_Direction = { 0.0f };

	// 方向ベクトルを合成
	// ジャンプした場合

	if (Jump && !Jumping)
	{
		// ジャンプ中でなければ
		// ジャンプ処理
		Jumping = true;					// ジャンプ中に設定(これステートでもいいかも)
		m_Velocity.y += m_JumpPower;	// 速度のY成分にジャンプ力を代入
		m_Direction.y += 1.0f;			// 上向きの方向ベクトルを加算
		Jump = false;
		Animation(JUMP);
	}
	// 下降している場合(ジャンプ中でベクトルのY成分が負(-)の時)
	if (Jumping && m_Velocity.y < 0.0f)
	{
		Animation(JUMP);
		// 地面に足がついた場合は方向ベクトルをリセット
		if (OnGround)
		{
			// 着地フラグを立てて
			Jumping = false;
			// 通常時アニメーションへ変更
			Animation(RUN);
		}
		else
		{
			// そうでない場合(下降中の場合)
			m_Direction.y -= 1.0f;	// 下向きの方向ベクトルを加算
		}
	}
	// 左移動しようとしている場合
	if (MoveLeft)
	{
		m_Direction.x -= 1.0f;	// 左向きの方向ベクトルを加算
		// ジャンプ中はジャンプモーション優先
		if (Jumping)
		{
			Animation(JUMP);
		}
		else {
			Animation(RUN);
		}
		MoveLeft = false;
	}
	// 右移動しようとしている場合
	if (MoveRight)
	{
		m_Direction.x += 1.0f;	// 右向きの方向ベクトルを加算
		// ジャンプ中はジャンプモーション優先
		if (Jumping)
		{
			Animation(JUMP);
		}
		else {
			Animation(RUN);
		}
		MoveRight = false;
	}

	// 正規化(長さを１に揃える)
	if (m_Direction.Length() > 0.0f)
	{
		m_Direction.Normalize();
	}
	else
	{
		m_Direction = { 0.0f, 0.0f, 0.0f };  // 明示的に方向ベクトルをリセット
	}

	// X成分の移動速度を方向ベクトルと移動速度から計算
	m_Velocity.x = m_Direction.x * m_MoveSpeed;


	// 地面の上にいない場合、重力分速度を減算
	if (!OnGround)
	{
		Jumping = true;
		m_Velocity.y -= 0.5f;	// 重力加速度実装の場合ここを変更
	}
	else {
		// 接地していればジャンプ中ではない
		Jumping = false;
		// 通常時アニメーションへ変更(立ち止まってる時にアニメーションはしたくないので、一番自然な状態の画像に設定)
		m_Number.y = 0;			// 2025/01/23 赤根: なぜか二枚目のほうに設定されるけど違和感はマシになったので一旦これで置いとく
	}

	// 移動処理
	Vector3 newpos = transform.GetPosition();
	newpos += m_Velocity;		// 方向ベクトルとX成分の移動速度を掛けた値の分だけ毎フレーム進む
	// 新しい座標を代入
	transform.SetPosition(newpos);


	// 吸い込み処理は引数が必要なのでシーンで直接行う

	//if (IsSuction)
	//{
	//	Suction();
	//}

	// 発射処理

	if (IsShot)
	{
		Shot();
		IsShot = false;
	}

}


/**
 * @brief 描画
 * 吸い込みエフェクト、子オブジェクトとして設定したUIのマガジンも描画する
*/
void Player::Draw(void)
{
	// まず自身の描画
	this->GameObject::Draw();

	// TODO:(完了)アニメーションの違和感を取る
	// TODO:アタッチされたオブジェクトの描画
	// TODO:ジャンプの先行入力取れてしまうのを直す

	// 擬音銃の吸い込み時の竜巻を描画したいが、今回竜巻はUIにしていて、オブジェクトとして登録してしまうと当たり判定を取ってしまうのでここで擬音銃の描画まで行う
	// 擬音銃を持っていれば
	if (m_Soundgun)
	{
		// 描画(この中で吸い込み中かを判定してる)
		m_Soundgun->Draw();
	}
}

/**
 * @brief 解放処理
*/
void Player::Uninit(void)
{
	for (auto& mag : m_Magazines) {
		// マガジンを全て開放
		mag->Uninit();
		// 所有権を捨てる
		mag.reset();
	}
	// マガジンのコンテナを空にする
	m_Magazines.clear();

	// 擬音銃の解放
	//m_Soundgun->Uninit();   //ここばぐる
	// 所有権を捨てる
	m_Soundgun.reset();

	// クロスヘアの解放
	//m_CrossHair->Uninit();
	m_CrossHair.reset();

	// プレイヤーの解放
	this->GameObject::Uninit();
}


/**
 * @brief アニメーション関数
 * @param どのアニメーションを再生するかの列挙型
 * 接地したときに左右移動キー押さないと通常時に戻らないのでそこも直す
 * TODO:2025/01/21 左向きに移動したときの処理がまだ！！！！！！！！！！！！！！
*/
void Player::Animation(STATE _Anim_Name)
{
	// 一番初めはアニメーション加算なのでCountUpをtrueに設定
	static bool CountUp = true;
	static bool CountDown = false;
	// ディレイ用フレームカウント変数
	static int framecount = 0;

	// UV番号最大値で割る→余りがあればまだ加算できる
	// 余りなし→アニメーション最終フレームなので減算開始
	// →行いたいアニメーションの種類だけ引数で送る→関数内で計算して加算中か減算中かを判断させればいい
	switch (_Anim_Name)
	{
	case NORMAL:
		// 通常時は何もしない(小刻みな縦揺れアニメーションとかあればここに書く)
		break;
	case RUN:
		// 通常移動時
		this->m_Number.y = 0;	// 一番上の段を使う

		// フレーム数加算
		framecount++;
		if (framecount == 3)
		{
			// 加算中は
			if (CountUp)
			{
				// アニメーション番号加算(アニメーションごとに分割数が違う場合はswitchで条件分けしてここに分割数を入れればおｋ)
				m_Number.x += 1;
				// アニメーション番号余りなし→アニメーション最終フレームなので減算開始
				if (m_Number.x % m_Split.x == 0)
				{
					CountDown = true;
					CountUp = false;
				}
			}
			// 減算中は
			if (CountDown)
			{
				// アニメーション番号加算
				m_Number.x -= 1;
				// アニメーション番号が0より小さい→アニメーションの開始フレームなので番号を0に戻して加算開始
				if (m_Number.x < 0)
				{
					m_Number.x = 0;
					CountUp = true;
					CountDown = false;
				}
			}
			framecount = 0;
		}
		break;
	case JUMP:
		// ここがややこしい
		// ・ジャンプしたとき→ジャンプ中ではなくジャンプフラグが立った時
		// ・上昇中のとき→ジャンプ中でベクトルのY成分が正(+)の時
		// ・下降中のとき→ジャンプ中でベクトルのY成分が負(-)の時
		// ・着地したとき→ジャンプ中で下向きのベクトルが0になった時(プレイヤーが地面に接触したとき)

		// ジャンプ時
		// ・ジャンプしたとき→ジャンプ中ではなくジャンプフラグが立った時
		if (!Jumping && Jump)
		{
			this->m_Number.y = 1;	// 二番目の段の
			this->m_Number.x = 0;	// 左を使う
		}
		// ・上昇中のとき→ジャンプ中でベクトルのY成分が正(+)の時
		if (Jumping && m_Velocity.y > 0.0f)
		{
			// 別画像がないので同じものを使う
			this->m_Number.y = 1;	// 二番目の段の
			this->m_Number.x = 0;	// 左を使う
		}
		// ・下降中のとき→ジャンプ中でベクトルのY成分が負(-)の時
		if (Jumping && m_Velocity.y < 0.0f)
		{
			this->m_Number.y = 1;	// 二番目の段の
			this->m_Number.x = 1;	// 右を使う
		}
		// ・着地したとき→ジャンプ中で下向きのベクトルが0になった時(プレイヤーが地面に接触したとき)
		if (Jumping && m_Velocity.y == 0)
		{
			this->m_Number.y = 1;	// 二番目の段の
			this->m_Number.x = 1;	// 右を使う
		}

		break;
		// ↓は画像内ので今のところ実装予定なし
	case DAMAGED:
		break;
	case ATTACKED:
		break;
	default:
		break;
	}
}


/**
 * @brief 子オブジェクトをセット
 * @param _child 子オブジェクトのポインタ
 *
 * 〇マガジン取得の流れ
 * 　・マガジンを拾う→タグをUIに変更→大きさと座標を変更、としたい
*/
void Player::SetChild(std::shared_ptr<GameObject> _child)
{
	// 設定する子オブジェクトがマガジンであれば(キャストできれば)
	if (auto casted = std::dynamic_pointer_cast<Magazine>(_child))
	{
		// マガジンの座標とスケールを変更する(ここをマガジン数によって変えたい)
		// どうする？
		// →マガジンの大きさをUI向きに変更→マガジン一個の大きさ分だけ右にずらして座標を設定すればいける？→いけた！

		// 大きさを代入
		casted->SetScale(Vector3(120.0f, 120.0f, 0.0f));
		// 一個目は「ドォン」を入れるマガジンなので、座標を直接設定
		if (m_Magazines.empty())
		{
			// 座標設定
			casted->SetPosition(Vector3(810.0f, 450.0f, 0.0f));
			// このマガジンだけ大きさを変える
			casted->SetScale(Vector3(300.0f, 300.0f, 0.0f));
		}
		// 二個目のマガジン(擬音銃に装填する用のマガジン)を追加する場合
		else if (m_Magazines.size() == 1)
		{
			// 座標設定
			casted->SetPosition(Vector3(-900.0f, 500.0f, 0.0f));
		}
		// 既にマガジンを一個以上所持している場合は
		else
		{
			// マガジン数を計算
			size_t magcnt = m_Magazines.size();

			// 描画したい座標を計算
			Vector3 newMagPos;
			// X座標はいちばん後ろのマガジンの座標から 追加するマガジンの大きさ / 2した値 を足した座標に表示する
			newMagPos.x = m_Magazines.back()->GetPosition().x + casted->GetScale().x;
			// Y座標も同じように設定
			newMagPos.y = m_Magazines.back()->GetPosition().y;
			// 座標を代入
			casted->SetPosition(newMagPos);
		}

		// プレイヤーのマガジンに追加して
		m_Magazines.push_back(casted);
		// 子オブジェクトとしても設定
		m_pChildren.push_back(casted);

		// プレイヤーをマガジンの親として設定する
		// shared_from_thisだけだとGameObject型になるので、Player型にキャストしてから渡す
		_child->SetParent(std::dynamic_pointer_cast<Player>(shared_from_this()));
	}
	// 擬音銃なら
	else if (auto casted = std::dynamic_pointer_cast<SoundGun>(_child))
	{
		// 子オブジェクトに設定
		m_Soundgun = casted;
		m_pChildren.push_back(casted);

		// 座標をプレイヤーの少し右に調整(これ座標変換できるようにしたい)
		Vector3 newpos = transform.GetPosition();
		newpos.x += transform.GetScale().x / 2 + casted->GetScale().x / 2;	// 擬音銃とプレイヤーの大きさのそれぞれ半分を足した値を加算して座標を設定
		casted->SetPosition(newpos);

	}
	// クロスヘアの場合
	else if (auto casted = std::dynamic_pointer_cast<CrossHair>(_child))
	{
		// 子オブジェクトに設定
		m_CrossHair = casted;
		m_pChildren.push_back(casted);
	}
	else
	{
		// 子オブジェクトに追加
		m_pChildren.push_back(_child);
	}
	// 子オブジェクト側にもこのオブジェクトを親として設定
	_child->SetParent(shared_from_this());
}


/**
 * @brief 擬音吸い込み関数
 *
 *
 * シーンで判定した擬音との当たり判定を使って当たった擬音の座標を移動させる
 *
 * →その擬音をマガジンに組み込む処理を追加する
 *  →プレイヤーと当たるまで吸い込んだら、マガジンに追加
 * @param _gion_pos
 * @param _p_pos
*/
bool Player::Suction(std::weak_ptr<GameObject> _gion)
{
	// フラグを立てて擬音銃の吸い込み処理を実行
	m_Soundgun->SetIsSuction(true);

	// 擬音銃の吸い込みの結果を返す
	return m_Soundgun->Suction(_gion);
}


/**
 * @brief 擬音銃のエイムの座標を基準に擬音を発射
 * @param _gion
 *
 * やること
 * →クロスヘアを擬音銃の子オブジェクトに設定→入力を取って操作可能にする→プレイヤーの発射関数でそのクロスヘア情報とマガジンに入ってる擬音情報を使えるようにする
 *
 * やりたいこと→使う擬音(マガジン)を決める→エイム操作(これはいつでもできるようにする)→発射
*/
void Player::Shot(void)
{

	//発射
	if (IsShot)
	{
		//==========================================
		//=======１月２６日現状======================
		//Playerの０度～１８０度までしか判定をとれていない
		//１８０度を超えると＋に変換される（例：２４０度で入力すると、１２０度で発射される）
		//==============================================================================


		Vector3 vertex;			// 
		float hypotenuse;		// 斜辺の二乗
		float root_hypotenuse;	// 平方根の計算をした斜辺
		float Radians;			// 角度
		float Degrees;			// 度
		float M_PI;				// 円周率

		//-----------式案----------//
		//Playerを中心にして,照準を合わせている場所をGetPosで取って,//
		//エイムして取ったポジションから、垂直に降ろして三点取る//

		//斜辺^2 = エイムして取ったX座標のポジション ^ 2 - (エイムして取ったポジションから、垂直に降ろしたX座標 - PlayerのX座標) ^ 2//
		//cosθ = (エイムして取ったポジションから、垂直に降ろしたX座標 - PlayerのX座標) / 斜辺

		Vector3 p_aim = m_CrossHair->GetPosition();				// クロスヘア座標
		Vector3 p_player = this->transform.GetPosition();		// プレイヤー座標
		Vector3 p_gion = m_Magazines[UseMagNumber]->GetBulletPointer()->GetPosition();		// 発射する擬音の座標
		vertex.x = p_aim.x - p_player.x;			// 照準とPlayerのX座標の差（底辺）
		vertex.y = p_aim.y - p_player.y;			// 照準とPlayerのY座標差  （高さ）
		hypotenuse = (vertex.y * vertex.y) + (vertex.x * vertex.x); //斜辺の計算（底辺の二乗＋高さの二乗＝斜辺の二乗）
		root_hypotenuse = std::sqrt(hypotenuse);	// 斜辺の平方根の計算(ここでベクトルの長さが求まる)

		// ベクトルを正規化
		Vector3 normalized_vector;
		normalized_vector.x = vertex.x / root_hypotenuse;
		normalized_vector.y = vertex.y / root_hypotenuse;




		///////////////////////////////////////////////////////////////////////////////////////
		///			連の頑張りを使うためにコメントアウト(↑で手計算してたので↓は使わないでいく)			///
		///////////////////////////////////////////////////////////////////////////////////////
		///*p_aimの位置が
		//  (vertex.y, vertex.x) = ( 1, 1)…第一象限
		//　(vertex.y, vertex.x) = (-1, 1)…第二象限
		//　(vertex.y, vertex.x) = (-1,-1)…第三象限
		//　(vertex.y, vertex.x) = ( 1,-1)…第四象限
		// って感じ*/
		//Radians = std::atan2(vertex.y, vertex.x); //p_aimのポジションが第何象限にあるか確認

		//// 発射したい方向→銃の向く方向を設定
		//// 角度をベクトルに変換
		//Vector3 direction;
		//direction.x = std::cos(Radians);	// ベクトルのX成分
		//direction.y = std::sin(Radians);	// ベクトルのY成分

		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////

		// 銃の向きを設定(↑で計算して正規化した方向ベクトルを使用)
		m_Soundgun->SetDirection(normalized_vector);



		// ここから下は毎フレーム呼び出す前提で書かれているので変更が必要

		// 擬音銃の発射関数を呼び出す→毎フレーム呼び出す想定で書かれてる
		/*p_gion.x += directionX * 5;
		p_gion.y += directionY * 5;*/

		// 擬音の座標を設定
		//m_Magazines[UseMagNumber]->GetBulletPointer()->SetPosition(p_gion);


		// 擬音の発射関数には減速力とかは気にしなくていい→0に設定する→まっすぐ飛んでいく
		// 使うマガジンの情報を受け取って擬音銃で発射
		m_Soundgun->Shot(m_Magazines[UseMagNumber]);

		// 発射フラグをリセット
		IsShot = false;
	}
}


/**
 * @brief 選択しているマガジン内の擬音の情報を返す関数
 * @return 装填されている擬音
*/
IOnomatopoeia* Player::GetLoadedBullet(void)
{
	// 装填中のマガジンに入ってる擬音を返す
	return m_Magazines[UseMagNumber]->GetBulletPointer();
}


/**
 * @brief 選択してるマガジンを返す関数
 * @return 選択中のマガジン
*/
std::shared_ptr<Magazine> Player::GetUsingMag(void)
{
	return m_Magazines[UseMagNumber];
}


// 射撃状態のゲッター、セッター
bool Player::GetIsShot(void)
{
	return IsShot;
}

void Player::SetIsShot(bool _flg)
{
	IsShot = _flg;
}

// 吸い込み状態のゲッターセッター
bool Player::GetIsSuction(void)
{
	return IsSuction;
}

void Player::SetIsSuction(bool _flg)
{
	IsSuction = _flg;
}

// 選択されているマガジン番号のセッターゲッター
void Player::SetMagNumber(int _num)
{
	this->UseMagNumber = _num;
}

int Player::GetMagNumber(void)
{
	return this->UseMagNumber;
}

// マガジン数のゲッター
size_t Player::GetMagCount(void)
{
	return m_Magazines.size();
}
