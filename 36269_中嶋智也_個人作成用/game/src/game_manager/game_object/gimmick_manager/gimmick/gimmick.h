#pragma once

#include "vivid.h"
#include "gimmick_id.h"

class IGimmick
{
public:
	// コンストラクタ
	IGimmick(int width, int height, GIMMICK_ID id);

	// デストラクタ
	virtual ~IGimmick(void) = default;

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// ギミックIDの取得
	GIMMICK_ID GetGimmickID(void);

protected:
	int					m_Width;		// 幅
	int					m_Height;		// 高さ
	vivid::Vector2		m_Position;		// 位置
	vivid::Vector2		m_Velocity;		// 速さ
	GIMMICK_ID			m_GimmickID;	// ギミックID

	static const float	m_scroll_speed;	// スクロールスピード
	static const float	m_friction;		// 摩擦
};
