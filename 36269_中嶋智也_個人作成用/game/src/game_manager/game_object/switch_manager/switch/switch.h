#pragma once

#include "vivid.h"
#include "switch_id.h"

class ISwitch
{
public:
	// コンストラクタ
	ISwitch(int width, int height, SWITCH_ID id);

	// デストラクタ
	virtual ~ISwitch(void) = default;

	// 初期化
	virtual void Initialize(const vivid::Vector2& position);

	// 更新
	virtual void Update(void);

	// 描画
	virtual void Draw(void);

	// 解放
	virtual void Finalize(void);

	virtual void OnPress(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 位置の取得
	vivid::Vector2 GetPosition(void);

	// ギミックIDの取得
	SWITCH_ID GetSwitchID(void);

	// ギミック発動フラグの取得
	bool GetOnFlag(void);

protected:
	int					m_Width;		// 幅
	int					m_Height;		// 高さ
	vivid::Vector2		m_Position;		// 位置
	vivid::Vector2		m_Velocity;		// 速さ
	SWITCH_ID			m_SwitchID;		// ギミックID

	static const float	m_scroll_speed;	// スクロールスピード
	static const float	m_friction;		// 摩擦
};
