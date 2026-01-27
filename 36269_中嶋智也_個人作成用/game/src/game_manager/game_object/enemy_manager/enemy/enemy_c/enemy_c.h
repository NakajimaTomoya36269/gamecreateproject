#pragma once

#include "../enemy.h"
#include "vivid.h"

class CEnemyC
	: public IEnemy
{
public:
	// コンストラクタ
	CEnemyC(void);

	// デストラクタ
	~CEnemyC(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

	// 床のアタリ判定
	bool OnGround(IStage* stage) override;

	// 攻撃
	void Attack(ICharacter* character) override;

private:
	static const int			m_width;		// 幅
	static const int			m_height;		// 高さ
	static const float			m_radius;		// 半径
	static const int			m_max_life;		// 最大ライフ
};