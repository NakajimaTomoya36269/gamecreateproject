#pragma once

#include "../enemy.h"
#include "vivid.h"

/*
====================================
  攻撃型の敵クラス（EnemyC）
  ・IEnemy を継承
  ・一定時間ごとに攻撃を行う敵
  ・プレイヤーとの距離や条件で Attack が呼ばれる想定
====================================
*/
class CEnemyC
	: public IEnemy
{
public:
	// コンストラクタ
	// ・EnemyC 固有のサイズ・半径・ライフを IEnemy に渡す
	CEnemyC(void);

	// デストラクタ
	// ・特別な解放処理は行わない
	~CEnemyC(void) = default;

	// 初期化
	// ・出現位置の設定
	// ・ライフ、攻撃タイマー、攻撃フラグの初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	// ・毎フレーム呼ばれる
	// ・移動、重力、攻撃タイマー更新などを処理
	void Update(void) override;

	// 描画
	// ・EnemyC 用のテクスチャ描画
	void Draw(void) override;

	// 解放
	// ・非アクティブ時に呼ばれる後処理
	void Finalize(void) override;

	// 床（足場）のアタリ判定
	// ・EnemyC が地面に接地しているかを判定
	// ・重力や位置補正を行う
	bool OnGround(IStage* stage) override;

	// 攻撃処理
	// ・一定時間ごとにプレイヤーを攻撃
	// ・AttackTimer と Attacked フラグで多重攻撃を防ぐ
	void Attack(ICharacter* character) override;

private:
	// EnemyC 固有の定数
	static const int		m_width;		// 敵の横幅
	static const int		m_height;		// 敵の高さ
	static const float	m_radius;		// 当たり判定用半径
	static const int		m_max_life;		// 最大ライフ
	static const float	m_attack_time;	// 次の攻撃までの待ち時間

	// 攻撃関連のメンバ変数
	float				m_AttackTimer;	// 攻撃クールタイム用タイマー
	bool				m_Attacked;		// 攻撃済みフラグ（連続攻撃防止）
};
