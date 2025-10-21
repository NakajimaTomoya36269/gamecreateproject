#pragma once

#include "vivid.h"
#include "character_id.h"

class CStage;

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
	virtual bool OnGround(CStage* stage);

	// キャラクターIDの取得
	CHARACTER_ID GetCharacterID(void);

	// カテゴリーの取得
	CHARACTER_CATEGORY GetCategory(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);
	
	// 位置の設定
	void SetPosition(const vivid::Vector2 position);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 重力の取得
	float GetGravity(void);

	// 重力の設定
	void SetGravity(float gravity);

	// アクティブフラグの取得
	bool GetActive(void);

	// アクティブフラグの設定
	void SetActive(bool active);

	// ライフの取得
	int GetMaxLife(void);

	// ライフの設定
	int GetLife(void);

protected:
	// 生きている
	virtual void Alive(void);

	// 死亡
	virtual void Dead(void);

	vivid::Vector2		m_Position;		// 位置
	vivid::Vector2		m_Velocity;		// 速さ
	int  				m_Width;		// 幅
	int				    m_Height;		// 高さ
	int					m_Life;			// ライフ
	int					m_MaxLife;		// 最大ライフ
	float				m_Radius;		// 半径
	float				m_Gravity;		// 重力
	bool				m_Active;		// アクティブフラグ
	bool				m_IsGround;		// 地面の上にいる判定
	CHARACTER_CATEGORY  m_Category;		// カテゴリー
	CHARACTER_ID		m_CharacterID;	// キャラクターID
	CHARACTER_STATE		m_State;		// 状態

	static const float  m_move_speed;	// 動く速さ
	static const float  m_gravity_speed;// 重力の強さ
};