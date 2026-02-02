#pragma once

#include "vivid.h"
#include "character_id.h"
#include "../../goal/goal.h"

// 前方宣言
class IStage;
class IEnemy;
class IItem;
class ISwitch;
class IBullet;

/*
================================
  キャラクターの状態
================================
*/
enum class CHARACTER_STATE
{
	ALIVE,	// 生存中
	DEAD,	// 死亡
};

/*
================================
  キャラクター基底クラス
================================
*/
class ICharacter
{
public:
	/*
	----------------------------
	  コンストラクタ / デストラクタ
	----------------------------
	*/
	// width,height : キャラクターのサイズ
	// radius       : 当たり判定用半径
	// life         : 初期ライフ
	// category     : キャラクターの種別（プレイヤー / 敵など）
	// character_id : キャラクターID
	ICharacter(int width, int height, float radius, int life,
		CHARACTER_CATEGORY category, CHARACTER_ID character_id);

	// 仮想デストラクタ
	virtual ~ICharacter(void);

	/*
	----------------------------
	  基本処理
	----------------------------
	*/
	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画（派生クラスで実装）
	virtual void Draw(void);

	// 解放処理
	virtual void Finalize(void);

	/*
	----------------------------
	  移動・物理関連
	----------------------------
	*/
	// 地面の上にいるかどうか
	virtual bool OnGround(IStage* stage);

	// ジャンプ処理
	virtual void Jump(IStage* stage);

	// 重力反転処理
	virtual void ChangeGravity(IStage* stage);

	/*
	----------------------------
	  ステージとの当たり判定
	----------------------------
	*/
	// 天井に当たっているか
	virtual bool CheckHitCeiling(IStage* stage);

	// 右壁に当たっているか
	virtual bool CheckHitRightWall(IStage* stage);

	// 左壁に当たっているか
	virtual bool CheckHitLeftWall(IStage* stage);

	/*
	----------------------------
	  オブジェクトとの当たり判定
	----------------------------
	*/
	// 敵との当たり判定
	virtual bool CheckHitEnemy(IEnemy* enemy);

	// アイテムとの当たり判定
	virtual bool CheckHitItem(IItem* item);

	// スイッチとの当たり判定
	virtual bool CheckHitSwitch(ISwitch* sw);

	// 弾との当たり判定
	virtual bool CheckHitBullet(IBullet* bullet);

	/*
	----------------------------
	  情報取得系
	----------------------------
	*/
	// キャラクターID取得
	CHARACTER_ID GetCharacterID(void);

	// カテゴリー取得
	CHARACTER_CATEGORY GetCategory(void);

	// 現在位置取得
	vivid::Vector2 GetPosition(void);

	// X座標のみ取得
	float GetPositionX(void);

	// 位置設定
	void SetPosition(const vivid::Vector2 position);

	// 幅取得
	int GetWidth(void);

	// 高さ取得
	int GetHeight(void);

	// アクティブ状態取得
	bool GetActive(void);

	// アクティブ状態設定
	void SetActive(bool active);

	// 最大ライフ取得
	int GetMaxLife(void);

	// 現在ライフ取得
	int GetLife(void);

	// 重力取得
	float GetGravity(void);

	// 重力設定
	void SetGravity(float gravity);

	// 中心座標取得
	vivid::Vector2 GetCenterPosition(void);

	// 重力反転フラグ取得
	bool GetGravityChange(void);

	// 重力反転フラグ設定
	void SetGravityChange(bool gravity);

	/*
	----------------------------
	  特殊処理
	----------------------------
	*/
	// ゴールとの当たり判定
	bool CheckHitGoal(CGoal& goal);

	// ジャンプ力アップ処理
	void JumpUp(IItem* item);

	// 無敵処理
	void Invincible(IItem* item);

	// 落下床処理
	void FallStage(IStage* stage);

protected:
	/*
	----------------------------
	  状態別処理
	----------------------------
	*/
	// 生存中処理
	virtual void Alive(void);

	// 死亡処理
	virtual void Dead(void);

	/*
	----------------------------
	  メンバ変数
	----------------------------
	*/
	vivid::Vector2	m_Position;			// 現在位置
	vivid::Vector2	m_Velocity;			// 移動速度
	vivid::Rect		m_Rect;				// 描画・当たり判定用矩形
	vivid::Vector2	m_Anchor;			// 描画基準点（中心）
	vivid::Vector2	m_Jump;				// ジャンプ量

	int				m_Width;			// 幅
	int				m_Height;			// 高さ
	int				m_Life;				// 現在ライフ
	int				m_MaxLife;			// 最大ライフ
	float			m_Radius;			// 円形当たり判定用半径
	float			m_Gravity;			// 重力値

	float			m_JumpUpTimer;		// ジャンプ強化残り時間
	float			m_InvincibleTimer;	// 無敵残り時間
	float			m_FallTimer;		// 落下床用タイマー

	bool			m_Active;			// 有効フラグ
	bool			m_GravityChange;	// 重力反転フラグ
	bool			m_JumpUp;			// ジャンプ強化中フラグ
	bool			m_InvincibleFlag;	// 無敵フラグ

	CHARACTER_CATEGORY	m_Category;		// キャラクター種別
	CHARACTER_ID		m_CharacterID;	// キャラクターID
	CHARACTER_STATE		m_State;		// 現在の状態

	/*
	----------------------------
	  共通定数
	----------------------------
	*/
	static const float	m_gravity_speed;		// 基本重力
	static const float	m_max_gravity;			// 重力最大値
	static const float	m_jump_power;			// 通常ジャンプ力
	static const float	m_jump_up_max_time;		// ジャンプ強化時間
	static const float	m_jump_up_power;		// ジャンプ強化時ジャンプ力
	static const float	m_invincible_max_time;	// 無敵最大時間
	static const float	m_fall_time;			// 落下床が落ちるまでの時間
};
