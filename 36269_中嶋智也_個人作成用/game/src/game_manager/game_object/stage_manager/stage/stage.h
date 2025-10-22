#pragma once
#include "vivid.h"

class CStage
{
public:
	// コンストラクタ
	CStage(void);

	// デストラクタ
	~CStage(void) = default;

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

	// 位置の取得
	vivid::Vector2 GetPosition(void);

private:
	static const int	m_width;
	static const int	m_height;
	static const float	m_scroll_speed;
	static const float	m_friction;

	vivid::Vector2		m_Position;
	vivid::Vector2		m_Velocity;
};