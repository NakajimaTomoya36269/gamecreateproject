#pragma once

#include "vivid.h"
#include "../enemy.h"

class CEnemyD
	: public IEnemy
{
public:
	// コンストラクタ
	CEnemyD(void);

	// デストラクタ
	~CEnemyD(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

	// 地面のアタリ判定
	bool OnGround(IStage* stage) override;

	// 攻撃
	void Attack(ICharacter* character) override;

private:
	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
	static const float		m_radius;	// 半径
	static const int		m_max_life;	// 最大ライフ
	static const float		m_attack_time;	// 攻撃時間

	float						m_AttackTimer;	// 攻撃タイマー
	bool						m_Attacked;		// 攻撃フラグ
};