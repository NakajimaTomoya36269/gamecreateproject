#pragma once

#include "vivid.h"
#include "../switch.h"

class CFloorSwitch
	: public ISwitch
{
public:
	// コンストラクタ
	CFloorSwitch(void);

	// デストラクタ
	~CFloorSwitch(void) = default;

	// 描画
	void Draw(void) override;

private:
	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
};