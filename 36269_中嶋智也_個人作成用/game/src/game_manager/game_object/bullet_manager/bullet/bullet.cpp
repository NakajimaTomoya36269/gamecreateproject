#include "bullet.h"

const float IBullet::m_scroll_speed = 60.0f;
const float IBullet::m_friction = 0.9f;

IBullet::IBullet(int width, int height, float radius, BULLET_ID id)
	: m_Width(width)
	, m_Height(height)
	, m_Radius(radius)
	, m_BulletID(id)
	, m_Rotation(0.0f)
	, m_ActiveFlag(true)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
	, m_Velocity(vivid::Vector2(0.0f, 0.0f))
	, m_ScrollVelocity(vivid::Vector2(0.0f, 0.0f))
	, m_Rect{ 0,0,m_Width,m_Height }
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Scale(vivid::Vector2(1.0f, 1.0f))
{
}

void IBullet::Initialize(const vivid::Vector2& position, float direction, float speed)
{
	m_Position = position;
	m_Velocity.x = cos(direction) * speed;
	m_Velocity.y = sin(direction) * speed;
	m_ActiveFlag = true;
	m_ScrollVelocity = vivid::Vector2(0.0f, 0.0f);
	m_Rotation = 0.0f;
}

void IBullet::Update(void)
{
	namespace keyboard = vivid::keyboard;

	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);

	if (right_move_key)
	{
		m_ScrollVelocity.x -= m_scroll_speed;
	}
	if (left_move_key)
	{
		m_ScrollVelocity.x += m_scroll_speed;
	}

	m_Position.x += m_ScrollVelocity.x * vivid::GetDeltaTime();
	m_ScrollVelocity.x *= m_friction;

	m_Position += m_Velocity;

	CheckArea();

	m_Rotation = atan2(m_Velocity.y, m_Velocity.x);
}

void IBullet::Draw(void)
{
}

void IBullet::Finalize(void)
{
}

vivid::Vector2 IBullet::GetPosition(void)
{
	return m_Position;
}

int IBullet::GetWidth(void)
{
	return m_Width;
}

int IBullet::GetHeight(void)
{
	return m_Height;
}

float IBullet::GetRadius(void)
{
	return m_Radius;
}

bool IBullet::GetActiveFlag(void)
{
	return m_ActiveFlag;
}

void IBullet::SetActiveFlag(bool active)
{
	m_ActiveFlag = active;
}

BULLET_ID IBullet::GetBulletID(void)
{
	return m_BulletID;
}

void IBullet::CheckArea(void)
{
	if (m_Position.x < 0.0f || m_Position.x >(float)vivid::WINDOW_WIDTH ||
		m_Position.y < 0.0f || m_Position.y >(float)vivid::WINDOW_HEIGHT)
	{
		m_ActiveFlag = false;
	}
}
