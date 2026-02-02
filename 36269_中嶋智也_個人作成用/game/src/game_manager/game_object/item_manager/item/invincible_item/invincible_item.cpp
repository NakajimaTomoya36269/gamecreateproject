#include "invincible_item.h"

const int	CInvincibleItem::m_width = 80;
const int	CInvincibleItem::m_height = 80;
const float	CInvincibleItem::m_radius = 40.0f;

CInvincibleItem::CInvincibleItem(void)
	: IItem(m_width, m_height, m_radius, ITEM_ID::INVINCIBLE_ITEM)
{
}

void CInvincibleItem::Draw(void)
{
	vivid::DrawTexture("data\\invincible_item.png", m_Position);
}
