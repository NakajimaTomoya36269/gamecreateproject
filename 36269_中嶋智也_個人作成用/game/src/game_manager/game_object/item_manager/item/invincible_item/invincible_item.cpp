#include "invincible_item.h"

const int CInvincibleItem::m_width = 30;
const int CInvincibleItem::m_height = 30;

CInvincibleItem::CInvincibleItem(void)
	: IItem(m_width, m_height, ITEM_ID::INVINCIBLE_ITEM)
{
}

void CInvincibleItem::Draw(void)
{
	vivid::DrawTexture("data\\enemy_a.png", m_Position);
}
