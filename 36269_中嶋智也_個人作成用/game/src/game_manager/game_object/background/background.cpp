#include "background.h"

const int	CBackGround::m_max_background_count = 2;
const int	CBackGround::m_width = 1920;
const int	CBackGround::m_height = 1080;
const float	CBackGround::m_scroll_speed = 60.0f;

CBackGround::CBackGround(void)
	: m_Position(nullptr)
	, m_Velocity(nullptr)
{
}

void CBackGround::Initialize(void)
{
	if (!m_Position)
		m_Position = new vivid::Vector2[m_max_background_count];
	if (!m_Velocity)
		m_Velocity = new vivid::Vector2[m_max_background_count];

	for (int i = 0; i < m_max_background_count; i++)
	{
		m_Position[i] = vivid::Vector2(i * (float)m_width, 0.0f);

		m_Velocity[i] = vivid::Vector2(m_scroll_speed, 0.0f);
	}
}

void CBackGround::Update(void)
{
	namespace keyboard = vivid::keyboard;

	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	for (int i = 0; i < m_max_background_count; i++)
	{
		if (right_move_key)
		{
			m_Position[i].x -= m_Velocity[i].x * vivid::GetDeltaTime();

			if (m_Position[i].x <= -m_width)
			{
				m_Position[i].x += m_width * m_max_background_count;
			}
		}
		if (left_move_key)
		{
			m_Position[i].x += m_Velocity[i].x * vivid::GetDeltaTime();

			if (m_Position[i].x >= m_width)
			{
				m_Position[i].x -= m_width * m_max_background_count;
			}
		}
	}
}

void CBackGround::Draw(void)
{
	for (int i = 0; i < m_max_background_count; i++)
	{
		vivid::DrawTexture("data\\background.png", m_Position[i]);
	}
}

void CBackGround::Finalize(void)
{
	delete[] m_Position;
	m_Position = nullptr;

	delete[] m_Velocity;
	m_Velocity = nullptr;
}
