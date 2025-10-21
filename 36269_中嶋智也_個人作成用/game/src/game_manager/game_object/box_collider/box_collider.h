#pragma once

#include "vivid.h"

class CBoxCollider
{
public:
	// コンストラクタ
	CBoxCollider(void) = default;

	// デストラクタ
	~CBoxCollider(void) = default;

	// インスタンスの取得
	static CBoxCollider& GetInstance(void);

	bool CheckBoxCollision(const vivid::Vector2& box_position1, const int box_width1, const int box_height1,
							const vivid::Vector2& box_position2, const int box_width2, const int box_height2);
};