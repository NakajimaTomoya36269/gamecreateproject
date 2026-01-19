#pragma once

#include "vivid.h"
#include "../stage.h"

class CFallFloor
	: public IStage
{
public:
	// コンストラクタ
	CFallFloor(void);

	// デストラクタ
	~CFallFloor(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Finalize(void) override;

private:
	static const int			m_width;		// 幅
	static const int			m_height;		// 高さ
	static const float			m_fall_speed;	// 落下速度
	static const float			m_return_time;	// 床が戻って来る時間

	vivid::Vector2				m_FallVelocity;	// 落下速度
	float						m_ReturnTimer;	// 床が戻って来るタイマー
	unsigned int				m_Color;		// 色
};