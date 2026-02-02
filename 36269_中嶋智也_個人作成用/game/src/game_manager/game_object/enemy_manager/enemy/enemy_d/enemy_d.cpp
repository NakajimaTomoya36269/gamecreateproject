#include "enemy_d.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../character_manager/character_manager.h"
#include "../../../../../utility/utility.h"

// EnemyD の定数定義
const int   CEnemyD::m_width = 40;           // 敵の横幅
const int   CEnemyD::m_height = 40;          // 敵の高さ
const float CEnemyD::m_radius = 20.0f;       // 当たり判定半径
const int   CEnemyD::m_max_life = 1;          // 最大ライフ
const float CEnemyD::m_attack_time = 50.0f;  // 攻撃間隔（フレーム）

/*
------------------------------------
 コンストラクタ
 ・EnemyD 固有のサイズ・半径・ライフを IEnemy に渡す
 ・攻撃関連変数の初期化
------------------------------------
*/
CEnemyD::CEnemyD(void)
	: IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYD)
	, m_AttackTimer(0.0f)    // 攻撃タイマー
	, m_Attacked(false)     // 攻撃可能フラグ
{
}

/*
------------------------------------
 初期化処理
 ・Enemy 共通の初期化
 ・攻撃タイマーとフラグをリセット
------------------------------------
*/
void CEnemyD::Initialize(const vivid::Vector2& position)
{
	IEnemy::Initialize(position);

	// 攻撃開始までの待ち時間をセット
	m_AttackTimer = m_attack_time;
	m_Attacked = false;
}

/*
------------------------------------
 更新処理
 ・Enemy 共通処理のみ
------------------------------------
*/
void CEnemyD::Update(void)
{
	IEnemy::Update();
}

/*
------------------------------------
 描画処理
 ・EnemyD のテクスチャを描画
------------------------------------
*/
void CEnemyD::Draw(void)
{
	vivid::DrawTexture("data\\enemy_b.png", m_Position);
}

/*
------------------------------------
 解放処理
 ・IEnemy 側の後処理を呼び出す
------------------------------------
*/
void CEnemyD::Finalize(void)
{
	IEnemy::Finalize();
}

/*
------------------------------------
 接地判定
 ・EnemyD は床判定を使わない
 ・拡張用に関数だけ用意
------------------------------------
*/
bool CEnemyD::OnGround(IStage* stage)
{
	if (!stage) return false;

	return false;
}

/*
------------------------------------
 攻撃処理
 ・一定時間ごとに上下どちらかへ弾を発射
 ・プレイヤーとの横距離のみで判定
------------------------------------
*/
void CEnemyD::Attack(ICharacter* character)
{
	if (!character) return;

	// 攻撃タイマーを進める
	if (++m_AttackTimer > m_attack_time)
	{
		m_Attacked = true;
	}

	// 自分から画面上端までの距離
	float dist_to_top = m_Position.y;

	// 自分から画面下端までの距離
	float dist_to_bottom = (float)vivid::WINDOW_HEIGHT - m_Position.y;

	// プレイヤーとの X 方向距離
	float distance = fabs(character->GetPosition().x - m_Position.x);

	// 攻撃可能距離
	const float attack_range = 500.0f;

	// 射程内かつ攻撃可能なら攻撃
	if (distance <= attack_range && m_Attacked)
	{
		CBulletManager& bullet_manager = CBulletManager::GetInstance();

		// 上の方が空いている場合は上へ発射
		if (dist_to_top >= dist_to_bottom)
		{
			bullet_manager.Create(
				BULLET_ID::NORMAL_BULLET, // 弾の種類
				GetCenterPosition(),     // 発射位置
				DEG_TO_RAD(270.0f),      // 上方向（270度）
				4.0f                     // 弾速
			);
		}
		// 下の方が空いている場合は下へ発射
		else
		{
			bullet_manager.Create(
				BULLET_ID::NORMAL_BULLET, // 弾の種類
				GetCenterPosition(),     // 発射位置
				DEG_TO_RAD(90.0f),       // 下方向（90度）
				4.0f                     // 弾速
			);
		}

		// 攻撃タイマーをリセット
		m_AttackTimer -= m_attack_time;

		// 次の攻撃まで待機
		m_Attacked = false;
	}
}
