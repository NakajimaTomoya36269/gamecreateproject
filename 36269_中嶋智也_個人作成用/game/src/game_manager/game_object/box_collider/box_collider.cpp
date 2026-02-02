#include "box_collider.h"

//------------------------------------------------------------
// シングルトンインスタンスの取得
//------------------------------------------------------------
CBoxCollider& CBoxCollider::GetInstance(void)
{
	// 関数内 static にすることで
	// 初回呼び出し時に一度だけ生成される
	static CBoxCollider instance;

	return instance;
}

//------------------------------------------------------------
// 矩形同士の当たり判定（AABB）
//------------------------------------------------------------
// box_position : 左上座標
// box_width    : 横幅
// box_height   : 高さ
//------------------------------------------------------------
bool CBoxCollider::CheckBoxCollision(
	const vivid::Vector2& box_position1, const int box_width1, const int box_height1,
	const vivid::Vector2& box_position2, const int box_width2, const int box_height2)
{
	// 4方向すべてが重なっているかを判定
	// ・右端が相手の左端より右
	// ・左端が相手の右端より左
	// ・下端が相手の上端より下
	// ・上端が相手の下端より上
	return (
		box_position1.x + (float)box_width1 > box_position2.x &&
		box_position1.x                      < box_position2.x + (float)box_width2 &&
		box_position1.y + (float)box_height1 > box_position2.y &&
		box_position1.y < box_position2.y + (float)box_height2
		);
}

//------------------------------------------------------------
// 矩形と円の当たり判定
//------------------------------------------------------------
// box_position   : 矩形の左上座標
// box_width      : 矩形の横幅
// box_height     : 矩形の高さ
// circle_position: 円の中心座標
// radius         : 円の半径
//------------------------------------------------------------
bool CBoxCollider::CheckCircleCollision(
	const vivid::Vector2& box_position, const int box_width, const int box_height,
	const vivid::Vector2& circle_position, const float radius)
{
	// 円の中心に最も近い矩形上の点
	vivid::Vector2 near_position(0.0f, 0.0f);

	//--- X方向の最近点を求める ---
	if (circle_position.x < box_position.x)
	{
		// 円が矩形の左側にある
		near_position.x = box_position.x;
	}
	else if (circle_position.x > box_position.x + (float)box_width)
	{
		// 円が矩形の右側にある
		near_position.x = box_position.x + (float)box_width;
	}
	else
	{
		// 円が矩形のX範囲内にある
		near_position.x = circle_position.x;
	}

	//--- Y方向の最近点を求める ---
	if (circle_position.y < box_position.y)
	{
		// 円が矩形の上側にある
		near_position.y = box_position.y;
	}
	else if (circle_position.y > box_position.y + (float)box_height)
	{
		// 円が矩形の下側にある
		near_position.y = box_position.y + (float)box_height;
	}
	else
	{
		// 円が矩形のY範囲内にある
		near_position.y = circle_position.y;
	}

	// 円の中心から最近点までの距離ベクトル
	float dx = circle_position.x - near_position.x;
	float dy = circle_position.y - near_position.y;
	vivid::Vector2 diff(dx, dy);

	// 距離が半径以下なら当たっている
	return vivid::Vector2::Length(diff) <= radius;
}
