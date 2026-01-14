#include "switch.h"

const float ISwitch::m_scroll_speed = 60.0f;
const float ISwitch::m_friction = 0.9f;

ISwitch::ISwitch(int width, int height, SWITCH_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_SwitchID(id)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_OnFlag(false)
{
}

void ISwitch::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_OnFlag = false;
}

void ISwitch::Update(void)
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

void ISwitch::Draw(void)
{
}

void ISwitch::Finalize(void)
{
}

void ISwitch::GimmickOn(void)
{
	m_OnFlag = !m_OnFlag;
}

int ISwitch::GetWidth(void)
{
	return m_Width;
}

int ISwitch::GetHeight(void)
{
	return m_Height;
}

vivid::Vector2 ISwitch::GetPosition(void)
{
	return m_Position;
}

SWITCH_ID ISwitch::GetSwitchID(void)
{
	return m_SwitchID;
}

bool ISwitch::GetOnFlag(void)
{
	return m_OnFlag;
}
