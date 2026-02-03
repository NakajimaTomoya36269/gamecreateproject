#include "invincible_item.h"

//==================================================
// 定数定義
//==================================================

// 無敵アイテムの描画・当たり判定サイズ
const int   CInvincibleItem::m_width = 80;
const int   CInvincibleItem::m_height = 80;

// 円形当たり判定用半径（width / 2）
const float CInvincibleItem::m_radius = 40.0f;

//==================================================
// コンストラクタ
//==================================================
CInvincibleItem::CInvincibleItem(void)
// IItem にサイズ・当たり判定・アイテム種別を委譲
	: IItem(m_width, m_height, m_radius, ITEM_ID::INVINCIBLE_ITEM)
{
}

//==================================================
// 描画処理
//==================================================
void CInvincibleItem::Draw(void)
{
	// IItem 管理の座標を使用して描画
	vivid::DrawTexture("data\\invincible_item.png", m_Position);
}
