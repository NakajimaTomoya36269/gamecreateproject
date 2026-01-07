#pragma once

#include "vivid.h"
#include "../gimmick.h"

class CSwitch
	: public IGimmick
{
public:
	// コンストラクタ
	CSwitch(void);

	// デストラクタ
	~CSwitch(void) = default;

	// 描画
	void Draw(void) override;

private:
	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
};