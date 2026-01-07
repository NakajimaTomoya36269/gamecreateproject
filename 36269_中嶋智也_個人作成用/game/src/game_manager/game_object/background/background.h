#pragma once

#include "vivid.h"

class CBackGround
{
public:
	// コンストラクタ
	CBackGround(void);

	// デストラクタ
	~CBackGround(void) = default;

	// 初期化
	void Initialize(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

private:
	vivid::Vector2*			m_Position;		// 位置（ポインタ型）
	vivid::Vector2*			m_Velocity;		// 速さ（ポインタ型）

	static const int		m_max_background_count;		// 背景の数
	static const int		m_width;					// 幅
	static const int		m_height;					// 高さ
	static const float		m_scroll_speed;				// スクロールスピード
};