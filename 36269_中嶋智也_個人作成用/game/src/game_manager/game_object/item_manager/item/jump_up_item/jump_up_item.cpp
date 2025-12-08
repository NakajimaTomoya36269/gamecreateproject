#include "jump_up_item.h"

const int	CJumpUpItem::m_width = 30;
const int	CJumpUpItem::m_height = 30;

CJumpUpItem::CJumpUpItem(void)
	: IItem(m_width, m_height, ITEM_ID::JUMP_UP_ITEM)
{
}

void CJumpUpItem::Initialize(const vivid::Vector2& position)
{
	IItem::Initialize(position);
}

void CJumpUpItem::Update(void)
{
	IItem::Update();
}

void CJumpUpItem::Draw(void)
{
}

void CJumpUpItem::Finalize(void)
{
}
