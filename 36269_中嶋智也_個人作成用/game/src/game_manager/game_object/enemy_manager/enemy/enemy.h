#pragma once

#include "enemy_id.h"
#include "vivid.h"

class IStage;
class ICharacter;

enum class ENEMY_STATE
{
	ALIVE,
	DEAD,
};

class IEnemy
{
public:
	// コンストラクタ
	IEnemy(int width, int height, float radius, int life, ENEMY_ID enemy_id);

	// デストラクタ
	virtual ~IEnemy(void) = default;

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	// 床の当たり判定
	virtual bool OnGround(IStage* stage);

	virtual void Attack(ICharacter* character);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// 位置の設定
	void SetPosition(const vivid::Vector2& position);

	// 中心位置の取得
	vivid::Vector2 GetCenterPosition(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// アクティブフラグの取得
	bool GetActive(void);

	// アクティブフラグの設定
	void SetActive(bool active);

	// 動く範囲
	void MoveArea(void);

protected:
	// 生存
	virtual void Alive(void);

	// 死亡
	virtual void Dead(void);

	vivid::Vector2		m_Position;		// 位置
	vivid::Vector2		m_Velocity;		// 速さ
	vivid::Rect			m_Rect;			// 表示範囲
	vivid::Vector2		m_Anchor;		// 中心
	vivid::Vector2		m_MoveVelocity;	// 動く速さ
	vivid::Vector2		m_Jump;			// ジャンプ
	int  				m_Width;		// 幅
	int				    m_Height;		// 高さ
	int					m_Life;			// ライフ
	int					m_MaxLife;		// 最大ライフ
	float				m_Radius;		// 半径
	float				m_Gravity;		// 重力
	bool				m_Active;		// アクティブフラグ
	bool				m_MoveChange;	// 移動方向を変えるフラグ
	ENEMY_STATE			m_State;		// 状態
	ENEMY_ID			m_EnemyID;		// 敵ID
	IStage*				m_CurrentStage;

	static const float  m_gravity_speed;// 重力の強さ
	static const float	m_max_gravity;	// 重力最大値
	static const float	m_scroll_speed; // スクロールの速さ
	static const float  m_friction;		// 摩擦力
	static const float	m_move_speed;	// 動く速さ
	static const float	m_jump_power;	// ジャンプ力
};