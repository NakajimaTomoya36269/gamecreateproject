#pragma once

#include "vivid.h"
#include "../bullet.h"

class CNormalBullet
	: public IBullet
{
public:
	// コンストラクタ
	CNormalBullet(void);

	// デストラクタ
	~CNormalBullet(void) = default;

	// 初期化
	void Draw(void) override;

private:
	static const int		m_width;	// 幅
	static const int		m_height;	// 高さ
	static const float		m_radius;	// 半径
};