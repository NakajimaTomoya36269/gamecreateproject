#include "enemy_a.h"

const int	CEnemyA::m_width = 40;
const int	CEnemyA::m_height = 40;
const float CEnemyA::m_radius = 20.0f;
const int	CEnemyA::m_max_life = 1;
const float CEnemyA::m_max_speed = 1200.0f;

CEnemyA::CEnemyA(void)
	: IEnemy(m_width, m_height, m_radius, m_max_life, ENEMY_ID::ENEMYA)
{
}

void CEnemyA::Initialize(const vivid::Vector2& position)
{
	IEnemy::Initialize(position);

	m_Life = m_MaxLife = m_max_life;
}

void CEnemyA::Update(void)
{
	IEnemy::Update();
}

void CEnemyA::Draw(void)
{
	IEnemy::Draw();
	vivid::DrawTexture("data\\enemy_a.png", m_Position);
}

void CEnemyA::Finalize(void)
{
	IEnemy::Finalize();
}

void CEnemyA::Alive(void)
{
	//if (m_MoveVelocity.x < m_max_speed)
		m_MoveVelocity.x += m_move_speed;

	m_Position.x += m_MoveVelocity.x * vivid::GetDeltaTime();
	m_MoveVelocity.x *= m_friction;

	IEnemy::Alive();
	if (m_Position.y < 0.0f || m_Position.y + m_Height >(float)vivid::WINDOW_HEIGHT)
	{
		m_State = ENEMY_STATE::DEAD;
	}
}

void CEnemyA::Dead(void)
{
	m_Active = false;
	IEnemy::Dead();
}
