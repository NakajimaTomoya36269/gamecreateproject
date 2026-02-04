#include "normal_bullet.h"

//------------------------------------------------------------
// 通常弾の当たり判定サイズ定義
//------------------------------------------------------------
const int   CNormalBullet::m_width = 32;     // 弾の横幅
const int   CNormalBullet::m_height = 32;     // 弾の高さ
const float CNormalBullet::m_radius = 16.0f;  // 円判定用半径
// 基本的な弾の絵のファイルパス
const std::string CNormalBullet::m_normal_bullet_texture_path = "data\\ball.png";

//------------------------------------------------------------
// コンストラクタ
//------------------------------------------------------------
// 基底クラス IBullet にサイズと弾IDを渡す
CNormalBullet::CNormalBullet(void)
	: IBullet(m_width, m_height, m_radius, BULLET_ID::NORMAL_BULLET)
{
}

//------------------------------------------------------------
// 描画処理
//------------------------------------------------------------
void CNormalBullet::Draw(void)
{
	// 通常弾用の画像を描画
	// ・位置        : m_Position
	// ・描画矩形    : m_Rect
	// ・アンカー    : m_Anchor
	// ・スケール    : m_Scale
	// ・回転        : m_Rotation
	vivid::DrawTexture(
		m_normal_bullet_texture_path,
		m_Position,
		0xffffffff,
		m_Rect,
		m_Anchor,
		m_Scale,
		m_Rotation
	);
}
