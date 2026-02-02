#pragma once

#include "enemy_id.h"
#include "vivid.h"

// 前方宣言（循環インクルード防止）
class IStage;
class ICharacter;

/*
==================================================
 敵の状態
==================================================
*/
enum class ENEMY_STATE
{
	ALIVE,	// 生存中
	DEAD,	// 死亡
};

/*
==================================================
 敵 基底クラス
 ・全ての敵が継承する共通クラス
 ・移動 / 重力 / 床判定 / 状態管理を担当
==================================================
*/
class IEnemy
{
public:
	// コンストラクタ
	// width, height : 当たり判定サイズ
	// radius        : 円判定用半径
	// life          : ライフ
	// enemy_id      : 敵ID
	IEnemy(int width, int height, float radius, int life, ENEMY_ID enemy_id);

	// デストラクタ
	virtual ~IEnemy(void) = default;

	//====================================
	// 基本処理
	//====================================

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新（状態に応じて Alive / Dead を呼ぶ）
	virtual void Update(void);

	// 描画（派生クラスで実装）
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	//====================================
	// 判定・行動
	//====================================

	// 床との当たり判定
	// 戻り値 : 床の上にいるか
	virtual bool OnGround(IStage* stage);

	// 攻撃処理（派生クラスでオーバーライド前提）
	virtual void Attack(ICharacter* character);

	//====================================
	// Getter / Setter
	//====================================

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// 位置の設定
	void SetPosition(const vivid::Vector2& position);

	// 中心位置の取得（弾発射・距離判定用）
	vivid::Vector2 GetCenterPosition(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// アクティブフラグの取得
	bool GetActive(void);

	// アクティブフラグの設定
	void SetActive(bool active);

	// 半径の取得
	float GetRadius(void);

	//====================================
	// 移動制御
	//====================================

	// 床の範囲内を往復移動させる
	void MoveArea(void);

protected:
	//====================================
	// 状態別処理
	//====================================

	// 生存時処理
	virtual void Alive(void);

	// 死亡時処理
	virtual void Dead(void);

	//====================================
	// メンバ変数
	//====================================

	vivid::Vector2	m_Position;		// 位置
	vivid::Vector2	m_Velocity;		// 速度（重力・スクロール影響）
	vivid::Rect		m_Rect;			// 矩形当たり判定
	vivid::Vector2	m_Anchor;		// 中心点
	vivid::Vector2	m_MoveVelocity;	// 横移動用速度
	vivid::Vector2	m_Jump;			// ジャンプ量

	int				m_Width;		// 幅
	int				m_Height;		// 高さ
	int				m_Life;			// 現在ライフ
	int				m_MaxLife;		// 最大ライフ
	float			m_Radius;		// 半径
	float			m_Gravity;		// 重力加速度

	bool			m_Active;		// 有効フラグ
	bool			m_MoveChange;	// 移動方向反転フラグ

	ENEMY_STATE		m_State;		// 状態
	ENEMY_ID		m_EnemyID;		// 敵ID

	IStage* m_CurrentStage;// 現在乗っている床

	//====================================
	// 共通定数（全敵共通）
	//====================================

	static const float  m_gravity_speed;	// 重力の強さ
	static const float	m_max_gravity;		// 重力最大値
	static const float	m_scroll_speed;		// スクロール影響速度
	static const float  m_friction;			// 摩擦（減衰率）
	static const float	m_move_speed;		// 横移動速度
	static const float	m_jump_power;		// ジャンプ力
};
