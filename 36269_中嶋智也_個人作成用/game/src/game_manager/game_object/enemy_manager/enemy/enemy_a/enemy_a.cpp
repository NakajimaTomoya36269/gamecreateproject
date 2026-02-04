#include "enemy_a.h"

/*
====================================
  EnemyA 固有パラメータ
====================================
*/
const int	CEnemyA::m_width = 40;		// 敵の横幅
const int	CEnemyA::m_height = 40;		// 敵の高さ
const float CEnemyA::m_radius = 20.0f;	// 当たり判定用半径
const int	CEnemyA::m_max_life = 1;	// 最大ライフ
// 敵の絵のファイルパス
const std::string CEnemyA::m_enemy_texture_path = "data\\enemy_a.png";

/*
====================================
  コンストラクタ
  ・EnemyA 固有のサイズ / 半径 / ライフを
	IEnemy に渡して初期化
====================================
*/
CEnemyA::CEnemyA(void)
	: IEnemy(
		m_width,			// 幅
		m_height,			// 高さ
		m_radius,			// 半径
		m_max_life,			// 最大ライフ
		ENEMY_ID::ENEMYA	// 敵ID
	)
{
}

/*
====================================
  初期化
  ・基底クラスの初期化を実行
  ・ライフを最大値にリセット
====================================
*/
void CEnemyA::Initialize(const vivid::Vector2& position)
{
	// 基底クラス（IEnemy）の初期化
	IEnemy::Initialize(position);

	// ライフを最大値に設定
	m_Life = m_MaxLife = m_max_life;
}

/*
====================================
  更新処理
  ・基本的な移動や状態更新は
	IEnemy に任せる
====================================
*/
void CEnemyA::Update(void)
{
	IEnemy::Update();
}

/*
====================================
  描画処理
  ・共通描画処理を行った後
  ・EnemyA専用の画像を描画
====================================
*/
void CEnemyA::Draw(void)
{
	// 共通描画処理
	IEnemy::Draw();

	// EnemyA の画像描画
	vivid::DrawTexture(m_enemy_texture_path, m_Position);
}

/*
====================================
  終了処理
  ・基底クラスの終了処理を呼ぶ
====================================
*/
void CEnemyA::Finalize(void)
{
	IEnemy::Finalize();
}

/*
====================================
  生存状態の処理
  ・Y方向に移動
  ・画面外に出たら死亡状態へ
====================================
*/
void CEnemyA::Alive(void)
{
	// 共通の生存処理
	IEnemy::Alive();

	// Y方向移動
	m_Position.y += m_Velocity.y;

	// 画面上 or 画面下に出たら死亡
	if (m_Position.y < 0.0f ||
		m_Position.y + m_Height >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = ENEMY_STATE::DEAD;
	}
}

/*
====================================
  死亡状態の処理
  ・アクティブを無効化
  ・基底クラスの死亡処理を実行
====================================
*/
void CEnemyA::Dead(void)
{
	// 管理対象から外す
	m_Active = false;

	// 共通の死亡処理
	IEnemy::Dead();
}
