#pragma once

#include "../enemy.h"
#include "vivid.h"

class CEnemyA
	: public IEnemy
{
public:
	// コンストラクタ
	CEnemyA(void);

	// デストラクタ
	~CEnemyA(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

private:
	// 生存
	void Alive(void) override;

	// 死亡
	void Dead(void) override;

	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
	static const float		m_radius;	// 半径
	static const int		m_max_life;	// 最大ライフ
	static const float		m_move_speed;	// 動く速さ
	static const float		m_max_speed;	// 最大スピード

	vivid::Vector2			m_MoveVelocity;	// 動く速さ
};