#include "jump_up_item.h"

//==================================================
// 定数定義
//==================================================

// ジャンプ強化アイテムの描画・当たり判定サイズ
const int   CJumpUpItem::m_width = 80;
const int   CJumpUpItem::m_height = 80;

// 円形当たり判定用半径（width / 2）
const float CJumpUpItem::m_radius = 40.0f;

// アイテムの絵のファイルパス
const std::string CJumpUpItem::m_item_texture_path = "data\\jump_up_item.png";

//==================================================
// コンストラクタ
//==================================================
CJumpUpItem::CJumpUpItem(void)
// IItem にサイズ・当たり判定・アイテム種別を委譲
	: IItem(m_width, m_height, m_radius, ITEM_ID::JUMP_UP_ITEM)
{
}

//==================================================
// 描画処理
//==================================================
void CJumpUpItem::Draw(void)
{
	// IItem 管理の座標を使用して描画
	vivid::DrawTexture(m_item_texture_path, m_Position);
}
