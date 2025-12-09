#include "item.h"

const float IItem::m_scroll_speed = 60.0f;
const float	IItem::m_friction = 0.9f;

IItem::IItem(int width, int height, ITEM_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_ItemID(id)
	, m_ActiveFlag(true)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
{
}

IItem::~IItem(void)
{
}

void IItem::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_ActiveFlag = true;
}

void IItem::Update(void)
{
	namespace keyboard = vivid::keyboard;

	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	if (right_move_key)
	{
		m_Velocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x += m_scroll_speed;
	}

	m_Position += m_Velocity * vivid::GetDeltaTime();

	m_Velocity.x *= m_friction;
}

void IItem::Draw(void)
{
}

void IItem::Finalize(void)
{
}

int IItem::GetWidth(void)
{
	return m_Width;
}

int IItem::GetHeight(void)
{
	return m_Height;
}

vivid::Vector2 IItem::GetPosition(void)
{
	return m_Position;
}

bool IItem::GetActive(void)
{
	return m_ActiveFlag;
}

void IItem::SetActive(bool active)
{
	m_ActiveFlag = active;
}

ITEM_ID IItem::GetItemID(void)
{
	return m_ItemID;
}
