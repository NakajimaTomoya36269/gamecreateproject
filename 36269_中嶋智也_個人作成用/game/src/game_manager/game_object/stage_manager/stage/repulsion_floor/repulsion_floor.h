#pragma once

#include "../stage.h"
#include "vivid.h"

class CRepulsionFloor
	: public IStage
{
public:
	// コンストラクタ
	CRepulsionFloor(void);

	// デストラクタ
	~CRepulsionFloor(void) = default;

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 描画
	void Draw(void) override;

private:
	static const int			m_width;		// 幅
	static const int			m_height;		// 高さ
};