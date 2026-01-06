#include "invincible_item.h"

const int CInvincibleItem::m_width = 30;
const int CInvincibleItem::m_height = 30;

CInvincibleItem::CInvincibleItem(void)
	: IItem(m_width, m_height, ITEM_ID::INVINCIBLE_ITEM)
{
}

void CInvincibleItem::Initialize(const vivid::Vector2& position)
{
	IItem::Initialize(position);
}

void CInvincibleItem::Update(void)
{
	IItem::Update();
}

void CInvincibleItem::Draw(void)
{
	vivid::DrawTexture("data\\enemy_a.png", m_Position);
}

void CInvincibleItem::Finalize(void)
{
}
