#pragma once

#include "vivid.h"
#include "../enemy.h"

/*
==================================================
 EnemyD クラス
 ・一定時間ごとに攻撃を行う敵
 ・プレイヤーとの距離を見て弾を発射
 ・画面の上下どちらが空いているかで
   発射方向を切り替えるタイプの敵
==================================================
*/
class CEnemyD
	: public IEnemy
{
public:
	/*
	------------------------------------
	 コンストラクタ
	 ・EnemyD 固有のサイズやライフを
	   IEnemy に設定する
	------------------------------------
	*/
	CEnemyD(void);

	/*
	------------------------------------
	 デストラクタ
	 ・特別な解放処理は不要なので default
	------------------------------------
	*/
	~CEnemyD(void) = default;

	/*
	------------------------------------
	 初期化処理
	 ・生成位置を受け取って初期化
	 ・攻撃タイマーのリセットなどを行う
	------------------------------------
	*/
	void Initialize(const vivid::Vector2& position) override;

	/*
	------------------------------------
	 更新処理
	 ・Enemy 共通の更新処理を実行
	------------------------------------
	*/
	void Update(void) override;

	/*
	------------------------------------
	 描画処理
	 ・EnemyD のテクスチャを描画
	------------------------------------
	*/
	void Draw(void) override;

	/*
	------------------------------------
	 解放処理
	 ・Enemy 共通の後処理を行う
	------------------------------------
	*/
	void Finalize(void) override;

	/*
	------------------------------------
	 地面との当たり判定
	 ・EnemyD は床に依存しない挙動
	 ・将来拡張用に override だけ用意
	------------------------------------
	*/
	bool OnGround(IStage* stage) override;

	/*
	------------------------------------
	 攻撃処理
	 ・一定時間ごとに攻撃可能になる
	 ・プレイヤーとの距離を判定
	 ・画面の上下どちらに余裕があるかで
	   弾の発射方向を決定
	------------------------------------
	*/
	void Attack(ICharacter* character) override;

private:
	// ---- EnemyD 固有の定数 ----
	static const int		m_width;		// 敵の横幅
	static const int		m_height;		// 敵の高さ
	static const float		m_radius;		// 当たり判定の半径
	static const int		m_max_life;		// 最大ライフ数
	static const float		m_attack_time;	// 攻撃間隔（フレーム）
	static const std::string m_enemy_texture_path;	// 敵の絵のファイルパス

	// ---- 攻撃制御用メンバ変数 ----
	float	m_AttackTimer;	// 攻撃までの経過時間を管理するタイマー
	bool	m_Attacked;		// 攻撃可能状態かどうかのフラグ
};
