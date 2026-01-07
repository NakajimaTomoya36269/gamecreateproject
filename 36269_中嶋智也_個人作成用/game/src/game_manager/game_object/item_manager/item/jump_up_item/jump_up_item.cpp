#include "jump_up_item.h"

const int	CJumpUpItem::m_width = 30;
const int	CJumpUpItem::m_height = 30;

CJumpUpItem::CJumpUpItem(void)
	: IItem(m_width, m_height, ITEM_ID::JUMP_UP_ITEM)
{
}

void CJumpUpItem::Draw(void)
{
	vivid::DrawTexture("data\\jump_up_item.png", m_Position);
}
