#include "jump_up_item.h"

const int	CJumpUpItem::m_width = 80;
const int	CJumpUpItem::m_height = 80;
const float	CJumpUpItem::m_radius = 40.0f;

CJumpUpItem::CJumpUpItem(void)
	: IItem(m_width, m_height, m_radius, ITEM_ID::JUMP_UP_ITEM)
{
}

void CJumpUpItem::Draw(void)
{
	vivid::DrawTexture("data\\jump_up_item.png", m_Position);
}
