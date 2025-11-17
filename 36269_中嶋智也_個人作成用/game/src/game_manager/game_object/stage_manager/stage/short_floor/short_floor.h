#pragma once

#include "vivid.h"
#include "../stage.h"

class CShortFloor
	: public IStage
{
public:
	// コンストラクタ
	CShortFloor(void);

	// デストラクタ
	~CShortFloor(void);

	// 初期化
	void Initialize(const vivid::Vector2& position) override;

	// 描画
	void Draw(void) override;

private:
	static const int		m_width;		// 幅
	static const int		m_height;		// 高さ
};