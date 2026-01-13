#include "gimmick.h"

const float IGimmick::m_scroll_speed = 60.0f;
const float IGimmick::m_friction = 0.9f;

IGimmick::IGimmick(int width, int height, GIMMICK_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_GimmickID(id)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_OnFlag(false)
{
}

void IGimmick::Initialize(const vivid::Vector2& position)
{
	m_Position = position;
	m_Velocity = vivid::Vector2(0.0f, 0.0f);
	m_OnFlag = false;
}

void IGimmick::Update(void)
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

void IGimmick::Draw(void)
{
}

void IGimmick::Finalize(void)
{
}

void IGimmick::GimmickOn(void)
{
	m_OnFlag = !m_OnFlag;
}

int IGimmick::GetWidth(void)
{
	return m_Width;
}

int IGimmick::GetHeight(void)
{
	return m_Height;
}

vivid::Vector2 IGimmick::GetPosition(void)
{
	return m_Position;
}

GIMMICK_ID IGimmick::GetGimmickID(void)
{
	return m_GimmickID;
}

bool IGimmick::GetOnFlag(void)
{
	return m_OnFlag;
}
