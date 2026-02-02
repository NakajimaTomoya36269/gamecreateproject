#pragma once

#include "../enemy.h"
#include "vivid.h"

/*
====================================
  天井移動型の敵クラス（EnemyB）
  ・IEnemy を継承
  ・主に上方向（逆重力）で動作する敵
====================================
*/
class CEnemyB
	: public IEnemy
{
public:
	// コンストラクタ
	// ・EnemyB 固有のサイズやライフを IEnemy に渡す
	CEnemyB(void);

	// デストラクタ
	// ・特別な解放処理は無し
	~CEnemyB(void);

	// 初期化
	// ・出現位置を設定
	// ・ライフや内部状態を初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	// ・毎フレーム呼ばれる処理
	// ・基本挙動は IEnemy::Update に委譲
	void Update(void) override;

	// 描画
	// ・EnemyB 用のテクスチャを描画
	void Draw(void) override;

	// 解放
	// ・非アクティブ化時に呼ばれる
	void Finalize(void) override;

	// 床（足場）のアタリ判定
	// ・EnemyB は「天井側に接地する」特殊な挙動
	// ・重力や位置補正もここで処理
	bool OnGround(IStage* stage) override;

private:
	// 生存中の処理
	// ・上方向への移動
	// ・画面外判定
	void Alive(void) override;

	// 死亡時の処理
	// ・アクティブフラグをOFFにする
	void Dead(void) override;

	// EnemyB 固有定数
	static const int		m_width;	// 敵の横幅
	static const int		m_height;	// 敵の高さ
	static const float	m_radius;	// 当たり判定用半径
	static const int		m_max_life;	// 最大ライフ
};
