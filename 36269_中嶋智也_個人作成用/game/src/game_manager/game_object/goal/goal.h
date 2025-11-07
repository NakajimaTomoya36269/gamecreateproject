#pragma once

#include "vivid.h"

class CGoal
{
public:
	// コンストラクタ
	CGoal(void);

	// デストラクタ
	~CGoal(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position);
	
	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 解放
	void Finalize(void);

	// 幅の取得
	int GetWidth(void);

	// 高さの取得
	int GetHeight(void);

	// 位置
	vivid::Vector2 GetPosition(void);

private:

	static const int			m_width;		// 幅
	static const int			m_height;		// 高さ
	static const float			m_scroll_speed;	// スクロールの速さ
	static const float			m_friction;		// 摩擦力

	vivid::Vector2				m_Position;		// 位置
	vivid::Vector2				m_Velocity;		// 速度
};