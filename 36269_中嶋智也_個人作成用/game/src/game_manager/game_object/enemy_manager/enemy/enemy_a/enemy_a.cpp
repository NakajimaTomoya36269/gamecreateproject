#include "enemy_a.h"

const int	CEnemyA::m_width = 40;
const int	CEnemyA::m_height = 40;
const float CEnemyA::m_radius = 20.0f;
const int	CEnemyA::m_max_life = 1;

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
	vivid::DrawTexture("data\\enemy_a.png", m_Position);
}

void CEnemyA::Finalize(void)
{
	IEnemy::Finalize();
}

void CEnemyA::Alive(void)
{
	IEnemy::Alive();
}

void CEnemyA::Dead(void)
{
	IEnemy::Dead();
}
