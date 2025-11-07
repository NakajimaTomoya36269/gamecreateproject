#include "goal.h"

const int	CGoal::m_width = 128;
const int	CGoal::m_height = 128;
const float CGoal::m_scroll_speed = 60.0f;
const float CGoal::m_friction = 0.9f;

CGoal::CGoal(void)
	: m_Position(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
{
}

void CGoal::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	m_Velocity = vivid::Vector2(0.0f, 0.0f);
}

void CGoal::Update(void)
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

void CGoal::Draw(void)
{
	vivid::DrawTexture("data\\goal.png", m_Position);
}

void CGoal::Finalize(void)
{
}

int CGoal::GetWidth(void)
{
	return m_width;
}

int CGoal::GetHeight(void)
{
	return m_height;
}

vivid::Vector2 CGoal::GetPosition(void)
{
	return m_Position;
}
