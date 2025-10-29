#include "enemy_a.h"

const int	CEnemyA::m_width = 40;
const int	CEnemyA::m_height = 40;
const float CEnemyA::m_radius = 20.0f;
const int	CEnemyA::m_max_life = 1;
const float	CEnemyA::m_move_speed = 60.0f;
const float CEnemyA::m_friction = 0.9f;

CEnemyA::CEnemyA(void)
	: ICharacter(m_width, m_height, m_radius, m_max_life,
		CHARACTER_CATEGORY::ENEMY, CHARACTER_ID::ENEMYA)
	, m_Position(vivid::Vector2(0.0f, 0.0f))
{
}

void CEnemyA::Initialize(const vivid::Vector2& position)
{
	m_Position = position;

	ICharacter::Initialize(position);

	m_Life = m_MaxLife = m_max_life;
}

void CEnemyA::Update(void)
{
	ICharacter::Update();
}

void CEnemyA::Draw(void)
{
	vivid::DrawTexture("data\\enemy_a.png", m_Position);
}

void CEnemyA::Finalize(void)
{
	ICharacter::Finalize();
}

bool CEnemyA::OnGround(CStage* stage)
{
	return false;
}

void CEnemyA::Alive(void)
{
	namespace keyboard = vivid::keyboard;
	bool right_move_key = keyboard::Button(keyboard::KEY_ID::RIGHT);
	bool left_move_key = keyboard::Button(keyboard::KEY_ID::LEFT);
	if (right_move_key)
	{
		m_Velocity.x += m_move_speed;
	}
	if (left_move_key)
	{
		m_Velocity.x -= m_move_speed;
	}

	m_Position.x += m_Velocity.x * vivid::GetDeltaTime();

	m_Velocity.x *= m_friction;

	if (m_GravityChange)
	{
		m_Position.y -= m_Velocity.y;
	}
	if (!m_GravityChange)
	{
		m_Position.y += m_Velocity.y;
	}
	if (m_Position.y < 0.0f || m_Position.y >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = CHARACTER_STATE::DEAD;
	}
}

void CEnemyA::Dead(void)
{
	m_Active = false;
}
