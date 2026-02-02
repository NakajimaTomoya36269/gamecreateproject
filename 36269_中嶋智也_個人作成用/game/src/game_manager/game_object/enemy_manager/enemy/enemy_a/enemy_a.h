#pragma once

#include "../enemy.h"
#include "vivid.h"

/*
====================================
  EnemyA クラス
  ・IEnemy を継承した具体的な敵クラス
  ・主に落下型 or 単純挙動の敵を想定
====================================
*/
class CEnemyA
	: public IEnemy
{
public:
	// コンストラクタ
	// ・EnemyA 固有のサイズやライフは cpp 側で定義
	CEnemyA(void);

	// デストラクタ
	// ・動的確保は Manager 側で管理するため default
	~CEnemyA(void) = default;

	// 初期化
	// ・生成時の位置設定
	// ・ライフなどの初期化を行う
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	// ・毎フレーム呼ばれる
	// ・基本処理は IEnemy::Update に委譲
	void Update(void) override;

	// 描画
	// ・EnemyA 専用の画像を描画
	void Draw(void) override;

	// 解放
	// ・削除前の後処理
	void Finalize(void) override;

private:
	// 生存時の処理
	// ・移動処理や画面外チェックなど
	void Alive(void) override;

	// 死亡時の処理
	// ・非アクティブ化して Manager から削除される
	void Dead(void) override;

	/*
	====================================
	  EnemyA 固有ステータス（定数）
	  ・cpp 側で値を定義
	====================================
	*/
	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
	static const float		m_radius;	// 当たり判定用半径
	static const int		m_max_life;	// 最大ライフ
};
