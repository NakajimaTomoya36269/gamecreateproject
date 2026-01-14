#pragma once

#include "vivid.h"
#include "character_id.h"
#include "../../goal/goal.h"

class IStage;
class IEnemy;
class IItem;
class ISwitch;

enum class CHARACTER_STATE
{
	ALIVE,
	DEAD,
};

class ICharacter
{
public:
	// コンストラクタ
	ICharacter(int width, int height, float radius, int life, 
				CHARACTER_CATEGORY category, CHARACTER_ID character_id);

	// デストラクタ
	virtual ~ICharacter(void);

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	// 地面の上にいる判定
	virtual bool OnGround(IStage* stage);

	// ジャンプ
	virtual void Jump(IStage* stage);

	// 重力変更
	virtual void ChangeGravity(IStage* stage);

	// 天井にあたっているかの判定
	virtual bool CheckHitCeiling(IStage* stage);

	// 右壁にあたっているかの判定
	virtual bool CheckHitRightWall(IStage* stage);

	// 左壁にあたっているかの判定
	virtual bool CheckHitLeftWall(IStage* stage);

	// 敵のアタリ判定
	virtual bool CheckHitEnemy(IEnemy* enemy);

	// アイテムのアタリ判定
	virtual bool CheckHitItem(IItem* item);

	virtual bool CheckHitSwitch(ISwitch* sw);

	// キャラクターIDの取得
	CHARACTER_ID GetCharacterID(void);

	// カテゴリーの取得
	CHARACTER_CATEGORY GetCategory(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// X座標の位置を取得
	 float GetPositionX(void);
	
	// 位置の設定
	void SetPosition(const vivid::Vector2 position);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// アクティブフラグの取得
	bool GetActive(void);

	// アクティブフラグの設定
	void SetActive(bool active);

	// ライフの取得
	int GetMaxLife(void);

	// ライフの設定
	int GetLife(void);

	// 重力の取得
	float GetGravity(void);

	// 重力の設定
	void SetGravity(float gravity);

	// 重力変更フラグの取得
	bool GetGravityChange(void);

	// 重力変更フラグの設定
	void SetGravityChange(bool gravity);

	// ゴールとのアタリ判定
	bool CheckHitGoal(CGoal& goal);

	// ジャンプ力が上がる
	void JumpUp(IItem* item);

	// 無敵
	void Invincible(IItem* item);

protected:
	// 生存
	virtual void Alive(void);

	// 死亡
	virtual void Dead(void);

	vivid::Vector2		m_Position;		// 位置
	vivid::Vector2		m_Velocity;		// 速さ
	vivid::Rect			m_Rect;			// 表示範囲
	vivid::Vector2		m_Anchor;		// 中心
	vivid::Vector2		m_Jump;			// ジャンプ

	int  				m_Width;			// 幅
	int				    m_Height;			// 高さ
	int					m_Life;				// ライフ
	int					m_MaxLife;			// 最大ライフ
	float				m_Radius;			// 半径
	float				m_Gravity;			// 重力
	float				m_JumpUpTimer;		// ジャンプ力が上がる時間
	float				m_InvincibleTimer;	// 無敵時間
	bool				m_Active;			// アクティブフラグ
	bool				m_GravityChange;	// 重力変更フラグ
	bool				m_JumpUp;			// ジャンプ力が上がるフラグ
	bool				m_InvincibleFlag;	// 無敵フラグ
	CHARACTER_CATEGORY  m_Category;			// カテゴリー
	CHARACTER_ID		m_CharacterID;		// キャラクターID
	CHARACTER_STATE		m_State;			// 状態

	static const float  m_gravity_speed;		// 重力の強さ
	static const float	m_max_gravity;			// 重力最大値
	static const float	m_jump_power;			// ジャンプ力
	static const float	m_jump_up_max_time;		// ジャンプ力が上がる最大時間
	static const float	m_jump_up_power;		// ジャンプ力上昇
	static const float	m_invincible_max_time;	// 無敵最大時間
};