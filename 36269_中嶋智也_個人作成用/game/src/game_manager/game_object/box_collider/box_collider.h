#pragma once

#include "vivid.h"

class CBoxCollider
{
public:
	// インスタンスの取得
	static CBoxCollider& GetInstance(void);

	bool CheckBoxCollision(const vivid::Vector2& box_position1, const int box_width1, const int box_height1,
							const vivid::Vector2& box_position2, const int box_width2, const int box_height2);

private:
	// コンストラクタ
	CBoxCollider(void) = default;

	// コピーコンストラクタ
	CBoxCollider(const CBoxCollider& rhs) = delete;

	// デストラクタ
	~CBoxCollider(void) = default;

	// 代入演算子
	CBoxCollider operator=(const CBoxCollider& rhs) = delete;
};