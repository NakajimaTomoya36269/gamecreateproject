#pragma once

#include "vivid.h"
#include "bullet_id.h"

class IBullet
{
public:
	// コンストラクタ
	IBullet(int width, int height, float radius, BULLET_ID id);

	// デストラクタ
	virtual ~IBullet(void) = default;

	// 初期化
	virtual void Initialize(const vivid::Vector2& position, float direction, float speed);

	// 更新
	virtual void Update(void);
	
	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 半径の取得
	float GetRadius(void);

	// アクティブフラグの取得
	bool GetActiveFlag(void);

	// アクティブフラグの設定
	void SetActiveFlag(bool active);

	// バレットIDの取得
	BULLET_ID GetBulletID(void);

protected:
	// 有効範囲
	void CheckArea(void);

	int					m_Width;			// 幅
	int					m_Height;			// 高さ
	float				m_Radius;			// 半径
	float				m_Rotation;			// 回転値
	bool				m_ActiveFlag;		// アクティブフラグ
	BULLET_ID			m_BulletID;			// バレットID
	vivid::Vector2		m_Position;			// 位置
	vivid::Vector2		m_Velocity;			// 速さ
	vivid::Vector2		m_ScrollVelocity;	// スクロール速さ
	vivid::Rect			m_Rect;				// 表示範囲
	vivid::Vector2		m_Anchor;			// 基準点
	vivid::Vector2		m_Scale;			// 拡大率

	static const float	m_scroll_speed;		// スクロールスピード
	static const float	m_friction;			// 摩擦力
};