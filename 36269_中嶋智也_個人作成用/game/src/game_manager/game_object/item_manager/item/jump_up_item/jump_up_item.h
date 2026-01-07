#pragma once

#include "vivid.h"
#include "../item.h"

class CJumpUpItem
	: public IItem
{
public:
	// コンストラクタ
	CJumpUpItem(void);

	// デストラクタ
	~CJumpUpItem(void) = default;

	// 描画
	void Draw(void) override;

private:
	static const int	m_width;	// 幅
	static const int	m_height;	// 高さ
};